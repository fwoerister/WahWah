//
// Created by florian on 27.09.18.
//

#ifndef UGENTEST_CONTROLUGEN_H
#define UGENTEST_CONTROLUGEN_H

#include <assert.h>
#include "UGen.h"

template<typename parameterType>
class IController {
public:
    virtual void process_parameter(parameterType &param) {};
};

/***
 * This UGen is used for controling parameters of AudioUgens.
 * @tparam SubControlUGen
 * @tparam parameterType
 */
template<typename SubControlUGen, typename parameterType>
class ControlUGen : public UGen<SubControlUGen, parameterType>, public IController<parameterType> {
public:
    ControlUGen(size_t num_channels) : UGen<SubControlUGen,parameterType>{num_channels} {};

    // Don't need to resize channel for a Control UGen
    void resize_channels(size_t num_channels) = delete;

};


#endif //UGENTEST_CONTROLUGEN_H