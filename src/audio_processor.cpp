#include "audio_processor.hpp"

AudioProcessor::AudioProcessor(std::shared_ptr<lab::AudioContext> ac):ac(ac) {
    //init with empty;
   // inputBus = std::make_shared<lab::AudioBus>(1,0,false);
    inputNode = std::make_shared<lab::SampledAudioNode>(*ac);


    outputNode = std::make_shared<lab::RecorderNode>(*ac);
}

std::unique_ptr<lab::AudioBus> AudioProcessor::process(std::shared_ptr<lab::AudioBus> inputBus) {
    lab::AudioStreamConfig config;
    config.desired_samplerate = 44100;
    config.desired_channels = 2;
    config.device_index = 1;
    {
        lab::ContextRenderLock r(ac.get(), "audio_processor");
        inputNode->setBus(r, inputBus);
    }
    inputNode->schedule(0);
    ac->addAutomaticPullNode(outputNode);
    lab::AudioContext &cx = *ac;
    std::shared_ptr<lab::RecorderNode> recorder = outputNode;
    std::unique_ptr<lab::AudioBus> outputBus;
    bool completed = false;

    recorder->startRecording();

    ac->offlineRenderCompleteCallback =  [&cx,&recorder,&outputBus,&completed](){
        recorder->stopRecording();
        outputBus = recorder->createBusFromRecording(false);
        cx.removeAutomaticPullNode(recorder);
        completed = true;
    };

    ac->startOfflineRenderWithInput(inputBus);

    while (!completed) {
        std::this_thread::sleep_for(std::chrono::milliseconds (2L));
    }
    while (!completed) {
        std::this_thread::sleep_for(std::chrono::milliseconds (2L));
    }
    return outputBus;
}


