#include "effect_eq_processor.hpp"

EffectEQProcessor::EffectEQProcessor(lab::AudioContext &ac, std::vector<float> frequencies)
:EffectBasicProcessor
(ac) {
    this->frequencies = frequencies;
    for(int i=0;i < this->frequencies.size();i++) {
        std::shared_ptr<lab::BiquadFilterNode> node = std::make_shared<lab::BiquadFilterNode>(ac);
        node->frequency()->setValue(this->frequencies[i]);

        if(i == 0) {
            node->setType(lab::FilterType::LOWSHELF);
        }else if (i == this->frequencies.size()-1) {
            node->setType(lab::FilterType::HIGHSHELF);
        }else{
            node->setType(lab::FilterType::PEAKING);
            node->q()->setValue(0.5);
        }
        node->gain()->setValue(0.0);
        addInnerNode(node);
    }
}

void EffectEQProcessor::updateGain(std::vector<float> gains) {
    if(gains.size() != frequencies.size()) {
        throw "vector gains size can not mapping to frequencies";
    }
    for(int i=0;i<gains.size();i++) {
        std::shared_ptr<lab::BiquadFilterNode> node = reinterpret_cast<const std::shared_ptr<lab::BiquadFilterNode> &>(innerNodes[i]);
        node->gain()->setValue(gains[i]);
    }
    this->gains = gains;
}





