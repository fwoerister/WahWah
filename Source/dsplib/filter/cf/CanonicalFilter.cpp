//
// Created by florian on 23.09.18.
//

#include "CanonicalFilter.h"
#include <math.h>
#include <iostream>

void UGenState<CanonicalFilter>::on_init() {

}

void UGenState<CanonicalFilter>::reset() {

}

CanonicalFilter::CanonicalFilter(Mode mode, IController<float> &f_c_cntr) : mode{mode}, f_c_cntr{f_c_cntr}, f_c{440}, Q{1 / std::sqrt(3)} {}

CanonicalFilter::CanonicalFilter(Mode mode, IController<float> &f_c_cntr, float f_c) : mode{mode},f_c_cntr{f_c_cntr}, f_c{f_c},
                                                                                      Q{1 / std::sqrt(2)} {}

CanonicalFilter::CanonicalFilter(Mode mode, IController<float> &f_c_cntr, float f_c, float Q) : mode{mode},f_c_cntr{f_c_cntr}, f_c{f_c},
                                                                                               Q{Q} {}


void CanonicalFilter::process_sample(float &sample, size_t channel) {
    float K = std::tan(M_PI * f_c / states[channel].sample_rate);
    if (channel == 0) {
        f_c_cntr.process_parameter(f_c);
    }


    switch (mode) {
        case Mode::BANDPASS:
            states[channel].b_0 = K / ((std::pow(K, 2) * Q) + K + Q);
            states[channel].b_1 = 0;
            states[channel].b_2 = -K / ((std::pow(K, 2) * Q) + K + Q);
            states[channel].a_1 = (2 * Q * (std::pow(K, 2) - 1)) / (std::pow(K, 2) + K + Q);
            states[channel].a_2 = (std::pow(K, 2) * Q - K + Q) / (std::pow(K, 2) * Q + K + Q);
            break;
        case Mode::HIGHPASS:
            //TODO: Not supported yet!
            break;

        case Mode::LOWPASS:
            //TODO: Not supported yet!
            break;
    }

    states[channel].x_h =
            sample - states[channel].a_1 * states[channel].x_h_n_1 - states[channel].a_2 * states[channel].x_h_n_2;
    sample = states[channel].b_0 * states[channel].x_h + states[channel].b_1 * states[channel].x_h_n_1 +
             states[channel].b_2 * states[channel].x_h_n_2;

    //update state
    states[channel].x_h_n_2 = states[channel].x_h_n_1;
    states[channel].x_h_n_1 = states[channel].x_h;

}

void CanonicalFilter::on_init() {
    UGen::on_init();
}

void CanonicalFilter::set_frequency(float f_c) {
    this->f_c = f_c;
}
