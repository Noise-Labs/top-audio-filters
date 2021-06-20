#include "effect_basic_processor.hpp"

EffectBasicProcessor::EffectBasicProcessor(lab::AudioContext &ac):ac(ac) {
    innerNodes = std::vector<std::shared_ptr<lab::AudioNode>>();
}

void EffectBasicProcessor::setInput(std::shared_ptr<lab::AudioNode> inputNode) {
    if(innerNodes.empty()) {
        throw  "empty innerNodes, please create inner graph first";
    }
    //disconnect connected input first
    if(this->inputNode != nullptr) {
        ac.disconnect(firstNode(),inputNode);
    }
    this->inputNode = inputNode;
    ac.connect(firstNode(),inputNode);
}

void EffectBasicProcessor::setOutput(std::shared_ptr<lab::AudioNode> outputNode) {
    if(innerNodes.empty()) {
        throw  "empty innerNodes, please create inner graph first";
    }

    //disconnect connected output first
    if(this->outputNode != nullptr) {
        ac.disconnect(outputNode,lastNode());
    }
    this->outputNode = outputNode;
    ac.connect(outputNode,lastNode());
}

void EffectBasicProcessor::connectAsInput(EffectBasicProcessor &other) {
    setInput(other.lastNode());
}

void EffectBasicProcessor::connectAsOutput(EffectBasicProcessor &other) {
    setOutput(other.firstNode());
}

std::shared_ptr<lab::AudioNode> EffectBasicProcessor::firstNode() {
    if(innerNodes.empty()) {
        throw  "empty innerNodes, please create inner graph first";
    }
    return innerNodes[0];
}

std::shared_ptr<lab::AudioNode> EffectBasicProcessor::lastNode () {
    if(innerNodes.empty()) {
        throw  "empty innerNodes, please create inner graph first";
    }
    return innerNodes[innerNodes.size() - 1];
}

void EffectBasicProcessor::shutdown() {
    if(inputNode != nullptr) {
        ac.disconnect(firstNode(),inputNode);
    }
    if(outputNode != nullptr) {
        ac.disconnect(outputNode,lastNode());
    }
    if(inputNode != nullptr && outputNode != nullptr) {
        ac.connect(outputNode,inputNode);
    }

    inputNode = nullptr;
    outputNode = nullptr;

    for(int i=0; i < innerNodes.size();i++) {
        ac.disconnect(innerNodes[i]);
    }
    innerNodes.resize(0);
}

bool EffectBasicProcessor::setTurnOn() {
    if(!turnoff) {
        return true;
    }
    if(turnoff) {
        turnoff = false;
    }

    if(inputNode != nullptr && outputNode != nullptr) {
        ac.disconnect(outputNode, inputNode);
    }

    if(inputNode != nullptr) {
        setInput(inputNode);
    }
    if(outputNode != nullptr) {
        setOutput(outputNode);
    }
    return true;
}

bool EffectBasicProcessor::setTurnOff() {
    if(turnoff) {
        return true;
    }
    ac.disconnect(firstNode(),inputNode);
    ac.disconnect(outputNode,lastNode());
    ac.connect(inputNode,outputNode);
    turnoff = true;
    return true;
}

EffectBasicProcessor::~EffectBasicProcessor() {
    shutdown();
}

void EffectBasicProcessor::addInnerNode(std::shared_ptr<lab::AudioNode> node) {
    if(innerNodes.size() > 0) {
        ac.connect(node,lastNode());
    }
    innerNodes.push_back(node);
}

