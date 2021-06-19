#include "effect_reverb.hpp"

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
    return rand() / INT_MAX;
}


EffectReverb::EffectReverb(AudioContext &cx):AbstractEffectNode(cx) {
    preDelayNode = make_shared<DelayNode>(cx,10.0f);
    reverbNode = make_shared<ConvolverNode>(cx);
    wetNode = make_shared<GainNode>(cx);
    dryNode = make_shared<GainNode>(cx);

    cx.connect(wetNode,reverbNode);
    cx.connect(dryNode,wetNode);
}

void EffectReverb::setPreDelayTime(float timeInSecond) {
    preDelayTimeInSecond = timeInSecond;
    preDelayNode->delayTime()->setFloat(preDelayTimeInSecond);
}

void EffectReverb::setDecay(float decay) {
    int len = cx.sampleRate() * this->preDelayTimeInSecond;
    //AudioBus *impulse = new AudioBus(2,len,true);
    shared_ptr<AudioBus> impulse = make_shared<AudioBus>(2,len,true);
    AudioChannel* lc = impulse->channel(0);
    AudioChannel* rc = impulse->channel(1);
    for(int i=0;i < len;i++) {
        int n = reverse ? len - i : i;
        lc->mutableData()[i] = (floatRand() * 2 -1) * pow(1 - n/len,decay);
        rc->mutableData()[i] = (floatRand() * 2 -1) * pow(1 - n/len,decay);
    }
    reverbNode->setImpulse(impulse);
}

void EffectReverb::setMix(float mix) {
    mix = mix;
    wetNode->gain()->setValue(getWetLevel(mix));
    dryNode->gain()->setValue(getDryLevel(mix));
}

void EffectReverb::setInput(shared_ptr<AudioNode> input) {
    AbstractEffectNode::setInput(input);
    cx.connect(reverbNode,input);
}

void EffectReverb::setOutput(shared_ptr<AudioNode> output) {
    AbstractEffectNode::setInput(output);
    cx.connect(output,dryNode);
};


















