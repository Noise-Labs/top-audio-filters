#ifndef  TOP_AUDIO_FILTER_EFFECT_REVERB_PROCESSOR_H
#define TOP_AUDIO_FILTER_EFFECT_REVERB_PROCESSOR_H

#include "effect_basic_processor.hpp"

class EffectReverbProcessor: public EffectBasicProcessor {

private:
    float decay = 0.01;
    float reverbTime = 0.05; //05ms
    float mix = 0.5;
    bool reverse;
    std::shared_ptr<lab::ConvolverNode> reverbNode;
    std::shared_ptr< lab::GainNode> wetNode;
    std::shared_ptr<lab::GainNode> dryNode;

    void updateImpulse();


public:
    EffectReverbProcessor(lab::AudioContext &ac);
    void setDecay(float decay);
    void setReverbTime(float reverbTime);
    void setMix(float mix);
};

#endif