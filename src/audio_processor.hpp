#ifndef  TOP_AUDIO_FILTER_AUDIO_PROCESSOR_H
#define TOP_AUDIO_FILTER_AUDIO_PROCESSOR_H
#include <LabSound/LabSound.h>

class AudioProcessor {
public:
    std::shared_ptr<lab::AudioContext> ac;
    lab::AudioBus* inputBus;
    std::shared_ptr<lab::SampledAudioNode> inputNode;
    std::shared_ptr<lab::RecorderNode> outputNode;
    AudioProcessor(std::shared_ptr<lab::AudioContext> ac);
    std::unique_ptr<lab::AudioBus> process(std::shared_ptr<lab::AudioBus> inputBus);
 //   void shutdown();
};

#endif