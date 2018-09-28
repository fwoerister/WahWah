//
// Created by florian on 23.09.18.
//

#ifndef UGENTEST_UGEN_H
#define UGENTEST_UGEN_H

#include <vector>

struct UGenStateBase {
    float sample_rate;
    size_t max_block_size;
    bool initialized = false;

    UGenStateBase() = default;

    UGenStateBase(float sample_rate, size_t max_block_size) {
        this->init(sample_rate, max_block_size);
    }

    virtual ~UGenStateBase() = default;

    virtual void init(float sample_rate, size_t max_block_size) final {
        this->sample_rate = sample_rate;
        this->max_block_size = max_block_size;
        this->initialized = true;
        on_init();
    }

    virtual void on_init() {}

    virtual void reset() {}
};

template<typename SubType>
struct UGenState : UGenStateBase {
};

template<typename SubType>
using UGenStates = std::vector<UGenState<SubType>>;

template<typename SubType, typename dataType>
class UGen {

protected:
    UGenStates<SubType> states;
    size_t num_channels;
    float sample_rate;
    size_t max_samples;
    bool initialized = false;

    void reset_states() {
        for (auto &s: states) {
            s.init(sample_rate, max_samples);
        }

        UGen::on_init();
        this->initialized = true;
    }

public:

    UGen(): UGen(1) {};

    UGen(size_t num_channels) : num_channels{num_channels} {
        states = std::vector<UGenState<SubType>>(num_channels);
    };

    void init_states(float sample_rate, size_t max_samples) {
        this->sample_rate = sample_rate;
        this->max_samples = max_samples;

        UGen<SubType,dataType>::reset_states();
    }

    void resize_channels(size_t num_channels) {
        states.resize(num_channels);

        UGen<SubType,dataType>::reset_states();

    }

    virtual void on_init() {};
};


#endif //UGENTEST_UGEN_H
