#include "effect_reverb_processor.hpp"

float getDryLevel(float mix) {
    if(mix <= 0.5) {
        return 1;
    }
    return 1 - ((mix - 0.5) *2);
}

float getWetLevel(float mix) {
    if(mix >= 0.5) {
        return 1;
    }
    return 1 - ((0.5 - mix) *2);
}

float floatRand() {
    return rand() / (float)INT_MAX;
}

EffectReverbProcessor::EffectReverbProcessor(lab::AudioContext &ac)
:EffectBasicProcessor(ac) {
    reverbNode = std::make_shared<lab::ConvolverNode>(ac);
    wetNode = std::make_shared<lab::GainNode>(ac);
    dryNode = std::make_shared<lab::GainNode>(ac);
    addInnerNode(reverbNode);
    addInnerNode(dryNode);
    addInnerNode(wetNode);
}

void EffectReverbProcessor::setDecay(float decay) {
    decay = decay;
    updateImpulse();
}

void EffectReverbProcessor::setReverbTime(float reverbTime) {
    reverbTime = reverbTime;
    updateImpulse();
}

void EffectReverbProcessor::setMix(float mix) {
    mix = mix;
    dryNode->gain()->setValue(mix);
    wetNode->gain()->setValue(1.0 - mix);
}


void EffectReverbProcessor::updateImpulse() {
    int len = ac.sampleRate() * this->reverbTime;
    std::shared_ptr<lab::AudioBus> impulse = std::make_shared<lab::AudioBus>(2,len,true);
    lab::AudioChannel* lc = impulse->channel(0);
    lab::AudioChannel* rc = impulse->channel(1);
    for(int i=0;i < len;i++) {
        int n = reverse ? len - i : i;
        lc->mutableData()[i] = (floatRand() * 2.0 -1.0) * pow(1.0 - n/len,decay);
        rc->mutableData()[i] = (floatRand() * 2.0 -1.0) * pow(1.0 - n/len,decay);
    }
    reverbNode->setImpulse(impulse);
}
