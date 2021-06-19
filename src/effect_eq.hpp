#ifndef TOP_AUDIO_FILTER_EFFECT_EQ_H
#define TOP_AUDIO_FILTER_EFFECT_EQ_H
#include <vector>
#include <LabSound/LabSound.h>
#include "effect.hpp"

using namespace std;
using namespace lab;

/**
 * N bands EQ
 */
class EffectEQ:public AbstractEffectNode{
public:
    vector<float> frequencies;
    vector<float> pans;
    vector<shared_ptr<BiquadFilterNode>> filters;
    shared_ptr<BiquadFilterNode> sumNode;
    EffectEQ(AudioContext &cx, vector<float> frequencies);
    ~EffectEQ();
    void setGain(vector<float> pans);

    using AbstractEffectNode::setInput;
    void setInput(shared_ptr<AudioNode> input);

    void setOutput(shared_ptr<AudioNode> output);
};

#endif