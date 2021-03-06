//
// Created by florian on 23.09.18.
//

#ifndef UGENTEST_CANONICALFILTER_H
#define UGENTEST_CANONICALFILTER_H

#include "../base/AudioUGen.h"
#include "../base/ControlUGen.h"
#include <math.h>

class IIR_BandPass;

template<>
struct UGenState<IIR_BandPass> : public UGenStateBase {
    void on_init() override;

    void reset() override;

    float x_h_n_1;
    float x_h_n_2;

    float b_0, b_1, b_2, a_1, a_2;

    float x_h, y_n;
};

class IIR_BandPass : public AudioUGen<IIR_BandPass, float> {
private:
    float f_c;
    float f_b;

    IController<float> &f_c_cntr;


public:
    IIR_BandPass(IController<float> &f_c_cntr);
    IIR_BandPass(IController<float> &f_c_cntr, float f_c);
    IIR_BandPass(IController<float> &f_c_cntr, float f_c, float f_b);

    void attach_f_c_controller(IController<float> &cntr);

    void process_sample(float &sample, size_t channel) override;

    void on_init() override;

    void set_frequency(float f_c);

    void set_bandwidth(float f_b);

    void update_param() override;

};

#endif //UGENTEST_CANONICALFILTER_H
