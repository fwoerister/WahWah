//
// Created by florian on 27.09.18.
//

#ifndef UGENTEST_AUDIOUGEN_H
#define UGENTEST_AUDIOUGEN_H

#include "UGen.h"

/***
 *
 * This is a UGen that is used for generating Audio
 *
 * @tparam SubType
 * @tparam dataType
 */
template<typename SubType, typename dataType>
class AudioUGen : public UGen<SubType, dataType> {
public:

    AudioUGen(): UGen<SubType,dataType>() {};

    AudioUGen(size_t num_channels): UGen<SubType, dataType>(num_channels) {};

    virtual void process_sample(dataType &param, size_t channel) {};

    virtual void update_param() {};
};


#endif //UGENTEST_AUDIOUGEN_H