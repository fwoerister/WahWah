//
// Created by florian on 27.09.18.
//

#ifndef UGENTEST_SINOSCILATOR_H
#define UGENTEST_SINOSCILATOR_H


#include "../base/ControlUGen.h"

class SinOscilator;

template<>
struct UGenState<SinOscilator> : public UGenStateBase {
    float phase = 0;
};

class SinOscilator : public ControlUGen<SinOscilator, float> {

private:
    float freq;
    float amp;

public:
    SinOscilator();

    SinOscilator(float freq, float amp);

    void set_frequency(float freq);

    void set_amplitude(float amp);

    void process_parameter(float &param) override;
};


#endif //UGENTEST_SINOSCILATOR_H
