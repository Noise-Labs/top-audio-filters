#ifndef TOP_AUDIO_FILTER_EFFECT_REVERB_H
#define TOP_AUDIO_FILTER_EFFECT_REVERB_H
#include <LabSound/LabSound.h>
#include "effect.hpp"

class EffectReverb:public AbstractEffectNode {

private:
    shared_ptr<DelayNode> preDelayNode;
    float preDelayTimeInSecond;
    float mix;
    float decay;
    bool reverse;

    shared_ptr<ConvolverNode> reverbNode;
    shared_ptr<GainNode> wetNode;
    shared_ptr<GainNode> dryNode;

public:
    EffectReverb(AudioContext &cx);

    void setPreDelayTime(float timeInMS);

    void setMix(float mix);

    void setDecay(float decay);


    void setInput(shared_ptr<AudioNode> input);

    void setOutput(shared_ptr<AudioNode> output);
};


#endif