#include <LabSound/LabSound.h>
#include "../src/effect_eq.hpp"

using namespace lab;

inline std::pair<AudioStreamConfig, AudioStreamConfig> GetDefaultAudioDeviceConfiguration(const bool with_input = false)
{
    AudioStreamConfig inputConfig;
    AudioStreamConfig outputConfig;

    const std::vector<AudioDeviceInfo> audioDevices = lab::MakeAudioDeviceList();
    const AudioDeviceIndex default_output_device = lab::GetDefaultOutputAudioDeviceIndex();
    const AudioDeviceIndex default_input_device = lab::GetDefaultInputAudioDeviceIndex();

    AudioDeviceInfo defaultOutputInfo, defaultInputInfo;
    for (auto & info : audioDevices)
    {
        if (info.index == default_output_device.index) defaultOutputInfo = info;
        else if (info.index == default_input_device.index) defaultInputInfo = info;
    }

    if (defaultOutputInfo.index != -1)
    {
        outputConfig.device_index = defaultOutputInfo.index;
        outputConfig.desired_channels = std::min(uint32_t(2), defaultOutputInfo.num_output_channels);
        outputConfig.desired_samplerate = defaultOutputInfo.nominal_samplerate;
    }

    if (with_input)
    {
        if (defaultInputInfo.index != -1)
        {
            inputConfig.device_index = defaultInputInfo.index;
            inputConfig.desired_channels = std::min(uint32_t(1), defaultInputInfo.num_input_channels);
            inputConfig.desired_samplerate = defaultInputInfo.nominal_samplerate;
        }
        else
        {
            throw std::invalid_argument("the default audio input device was requested but none were found");
        }
    }

    return {inputConfig, outputConfig};
}


int main(int argc, char** argv) {
    std::unique_ptr<lab::AudioContext> context;
    const auto defaultAudioDeviceConfigurations = GetDefaultAudioDeviceConfiguration();
    context = lab::MakeRealtimeAudioContext(defaultAudioDeviceConfigurations.second, defaultAudioDeviceConfigurations.first);
    lab::AudioContext& ac = *context.get();

    std::shared_ptr<AudioBus> musicClip = MakeBusFromFile("samples/stereo-music-clip.wav", true);

    if (!musicClip)
        return -1;

    std::shared_ptr<SampledAudioNode> musicClipNode;


    musicClipNode = std::make_shared<SampledAudioNode>(ac);
    {
        ContextRenderLock r(context.get(), "ex_simple");
        musicClipNode->setBus(r, musicClip);
    }

  //  context->connect(context->device(), musicClipNode, 0, 0);

    vector<float> freqs = vector<float>(4);
    freqs[0] = 320;
    freqs[1] = 1000;
    freqs[2] = 3200;
    freqs[3] = 6400;

    EffectEQ eqNode = EffectEQ(ac,freqs);
    eqNode.setGain(vector<float>{
        0.0,
        0.0,
        0.0,
        0.0});
    eqNode.setInput(musicClipNode);
    eqNode.setOutput(context->device());
    musicClipNode->schedule(0.0);
    std::this_thread::sleep_for(std::chrono::seconds(6));
}