#include "effect_eq.hpp"

EffectEQ::EffectEQ( AudioContext &cx, vector<float> frequencies) : AbstractEffectNode(cx){
    this->frequencies = frequencies;
    this->sumNode = make_shared<BiquadFilterNode>(cx);

    filters = vector< shared_ptr<BiquadFilterNode>>();
    for(int i =0;i < frequencies.size();i++) {
        shared_ptr<BiquadFilterNode> f = make_shared<BiquadFilterNode>(cx);

        if(i == 0) {
            f->setType(FilterType::LOWSHELF);
        }else if (i == frequencies.size() -1) {
            f->setType(FilterType::PEAKING);
            f->q()->setValue(0.5f);
        }else {
            f->setType(FilterType::HIGHSHELF);
        }
        f->frequency()->setValue(frequencies[i]);
        filters.push_back(f);
        if(i >0) {
            cx.connect(filters[i], filters[i-1]);
        }
    }
}

void EffectEQ::setInput(shared_ptr<AudioNode> input) {
    AbstractEffectNode::setInput(input);
    cx.connect(filters[0],input);
};

void EffectEQ::setOutput(shared_ptr<AudioNode> output) {
    AbstractEffectNode::setOutput(output);
    cx.connect(output,filters[filters.size() - 1]);
}

void EffectEQ::setGain(vector<float> pans) {
    for(int i=0;i<filters.size();i++) {
        filters[i]->gain()->setValue(pans[i]);
    }
}

EffectEQ::~EffectEQ() {
    for(int i=0;i < filters.size();i++) {
        cx.disconnect(filters[i],input);
    }
    cx.disconnect(output,sumNode);
}

