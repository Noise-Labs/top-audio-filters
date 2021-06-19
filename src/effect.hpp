#ifndef TOP_AUDIO_FILTER_EFFECT_H
#define TOP_AUDIO_FILTER_EFFECT_H
#include <vector>
#include <LabSound/LabSound.h>

using namespace std;
using namespace lab;

class AbstractEffectNode {
public:
    AudioContext& cx;
    shared_ptr<AudioNode> input;
    shared_ptr<AudioNode> output;

    AbstractEffectNode(AudioContext& cx);

    void setInput(shared_ptr<AudioNode> input);
    void setOutput(shared_ptr<AudioNode> output);
};

#endif