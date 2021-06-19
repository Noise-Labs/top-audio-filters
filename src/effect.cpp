#include "effect.hpp"

AbstractEffectNode::AbstractEffectNode(AudioContext &cx):cx(cx) {

}

void AbstractEffectNode::setInput(shared_ptr<AudioNode> input) {
    this->input = input;
}

void AbstractEffectNode::setOutput(shared_ptr<AudioNode> output) {
    this->output = output;
}
