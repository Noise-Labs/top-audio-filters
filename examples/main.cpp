#include <LabSound/LabSound.h>
#include "../src/top_audio_filter.h"

int main(int argc, char** argv) {
    auto context = makeOfflineAudioContext();
    AudioProcessor processor(std::move(context));

    std::shared_ptr<lab::AudioBus> musicClip = lab::MakeBusFromFile("samples/stereo-music-clip.wav", true);

    std::vector<float> freqs = std::vector<float>(4);
    freqs[0] = 320;
    freqs[1] = 1000;
    freqs[2] = 3200;
    freqs[3] = 6400;



    EffectEQProcessor effectEqProcessor(*processor.ac,freqs);

    effectEqProcessor.updateGain(std::vector<float>{
            0.0,
            0.0,
            0.0,
            0.0});
  effectEqProcessor.setInput(processor.inputNode);
  effectEqProcessor.setOutput(processor.outputNode);

    auto output = processor.process(musicClip);
    std::cout << "Output Channels:" << output->numberOfChannels() << std::endl;
    std::cout << "Output Channels:" << output->channel(0)->length() << std::endl;
    {

        auto output2 = processor.process(musicClip);

        std::cout << "Output Channels:" << output2->numberOfChannels() << std::endl;
        std::cout << "Output Channels:" << output2->channel(0)->length() << std::endl;
        lab::AudioChannel *c = output2->channel(0);
        for(int i=0; i <c->length();i++) {
            if(i % 1000 != 0) {
                continue;
            }
            std::cout << c->data()[i] << " ";
        }
    }


    /*
    {
        lab::ContextRenderLock r(processor.ac.get(), "audio_processor");
        processor.inputNode->setBus(r, musicClip);
    }
   effectEqProcessor.setInput(processor.inputNode);
    effectEqProcessor.setOutput(processor.ac->device());
   // processor.ac->connect(processor.ac->device(),processor.inputNode);
    processor.inputNode->schedule(0);
    std::this_thread::sleep_for(std::chrono::milliseconds (2000L));
  //
  //  std::cout <<"Output Size: " << output->channel(0)->length() << std::endl;
     */
};