//
// Created by florian on 23.09.18.
//

#ifndef UGENTEST_CANONICALFILTER_H
#define UGENTEST_CANONICALFILTER_H

#include "../../base/AudioUGen.h"
#include "../../base/ControlUGen.h"
#include <math.h>

class CanonicalFilter;

enum Mode {
    LOWPASS, BANDPASS, HIGHPASS
};

template<>
struct UGenState<CanonicalFilter> : public UGenStateBase {
    void on_init() override;

    void reset() override;

    float x_h_n_1;
    float x_h_n_2;

    float b_0, b_1, b_2, a_1, a_2;

    float x_h, y_n;
};

class CanonicalFilter : public AudioUGen<CanonicalFilter, float> {
private:
    float Q;
    Mode mode;
    float f_c;

    IController<float> &f_c_cntr;


public:
    CanonicalFilter(Mode mode, IController<float> &f_c_cntr);
    CanonicalFilter(Mode mode, IController<float> &f_c_cntr, float f_c);
    CanonicalFilter(Mode mode, IController<float> &f_c_cntr, float f_c, float Q);

    void attach_f_c_controller(IController<float> &cntr);

    void process_sample(float &sample, size_t channel) override;

    void on_init() override;

    void set_frequency(float f_c);


};

#endif //UGENTEST_CANONICALFILTER_H
