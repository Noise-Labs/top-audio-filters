#ifndef  TOP_AUDIO_FILTER_EFFECT_BASIC_PROCESSOR_H
#define TOP_AUDIO_FILTER_EFFECT_BASIC_PROCESSOR_H

#include <LabSound/LabSound.h>
#include <vector>
/// a effect basic processor chains many "AudioBasicProcessorNode", combined them as a music effect
class EffectBasicProcessor {

protected:
    std::shared_ptr<lab::AudioNode> inputNode = nullptr;
    std::shared_ptr<lab::AudioNode> outputNode = nullptr;
    bool turnoff = false;
    void addInnerNode(std::shared_ptr<lab::AudioNode> node);
public:
    lab::AudioContext &ac;

    EffectBasicProcessor(lab::AudioContext &ac);

    /// managing all inner nodes, and use the first node as InputNode
    /// the last node as OutputNode
    std::vector<std::shared_ptr<lab::AudioNode>>           innerNodes;

    std::shared_ptr<lab::AudioNode> firstNode();
    std::shared_ptr<lab::AudioNode> lastNode();

    void setInput( std::shared_ptr<lab::AudioNode> inputNode);

    void setOutput(std::shared_ptr<lab::AudioNode> outputNode);

    void connectAsInput(EffectBasicProcessor &other);
    void connectAsOutput(EffectBasicProcessor &other);

    void shutdown();
    bool setTurnOff();
    bool setTurnOn();




    ~EffectBasicProcessor();

};

#endif
