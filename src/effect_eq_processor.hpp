#ifndef  TOP_AUDIO_FILTER_EFFECT_EQ_PROCESSOR_H
#define TOP_AUDIO_FILTER_EFFECT_EQ_PROCESSOR_H

#include "effect_basic_processor.hpp"


/// N bands EQ Effect
class EffectEQProcessor: public EffectBasicProcessor {
public:
    std::vector<float> frequencies; // defined frequencies band.
    std::vector<float> gains; // band gain. -24 - +24
    EffectEQProcessor(lab::AudioContext &ac,std::vector<float> frequencies);
    void updateGain(std::vector<float> gains);
};

#endif