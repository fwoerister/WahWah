//
// Created by florian on 27.09.18.
//

#include "SinOscilator.h"
#include <math.h>
#include <iostream>

SinOscilator::SinOscilator(): SinOscilator(1.0f, 20.0f) {}

SinOscilator::SinOscilator(float freq, float amp) :ControlUGen(1), freq(freq), amp(amp) {}

void SinOscilator::process_parameter(float &param) {
    states[0].phase += std::fmod(1/states[0].sample_rate, M_PI_2);
    param = 500+amp*std::sin(M_PI_2 * freq * states[0].phase);
}


void SinOscilator::set_frequency(float freq) {
    this->freq = freq;
}

void SinOscilator::set_amplitude(float amp) {
    this->amp = amp;
}