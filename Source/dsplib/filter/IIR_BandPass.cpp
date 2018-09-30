//
// Created by florian on 23.09.18.
//

#include "IIR_BandPass.h"
#include <math.h>
#include <iostream>

void UGenState<IIR_BandPass>::on_init() {

}

void UGenState<IIR_BandPass>::reset() {

}

IIR_BandPass::IIR_BandPass(IController<float> &f_c_cntr) : f_c_cntr{f_c_cntr}, f_c{440}, f_b{100} {}

IIR_BandPass::IIR_BandPass(IController<float> &f_c_cntr, float f_c) : f_c_cntr{f_c_cntr}, f_c{f_c}, f_b{100} {}

IIR_BandPass::IIR_BandPass(IController<float> &f_c_cntr, float f_c, float f_b) : f_c_cntr{f_c_cntr}, f_c{f_c},
                                                                                 f_b{f_b} {}


void IIR_BandPass::process_sample(float &sample, size_t channel) {
    float K = std::tan(M_PI * f_c / states[channel].sample_rate);
    float Q = f_c / f_b;



    states[channel].b_0 = K / ((std::pow(K, 2) * Q) + K + Q);
    states[channel].b_1 = 0;
    states[channel].b_2 = -K / ((std::pow(K, 2) * Q) + K + Q);
    states[channel].a_1 = (2 * Q * (std::pow(K, 2) - 1)) / (std::pow(K, 2) + K + Q);
    states[channel].a_2 = (std::pow(K, 2) * Q - K + Q) / (std::pow(K, 2) * Q + K + Q);

    states[channel].x_h =
            sample - states[channel].a_1 * states[channel].x_h_n_1 - states[channel].a_2 * states[channel].x_h_n_2;

    sample = states[channel].b_0 * states[channel].x_h + states[channel].b_1 * states[channel].x_h_n_1 +
             states[channel].b_2 * states[channel].x_h_n_2;

    //update state
    states[channel].x_h_n_2 = states[channel].x_h_n_1;
    states[channel].x_h_n_1 = states[channel].x_h;

}

void IIR_BandPass::on_init() {
    UGen::on_init();
}

void IIR_BandPass::set_frequency(float f_c) {
    this->f_c = f_c;
}

void IIR_BandPass::set_bandwidth(float f_b) {
    this->f_b = f_b;
};

void IIR_BandPass::update_param(){
    f_c_cntr.process_parameter(f_c);
}