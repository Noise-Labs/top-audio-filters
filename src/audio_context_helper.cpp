#include "audio_context_helper.hpp"

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



std::unique_ptr<lab::AudioContext> makeRealTimeAudioContext() {
    auto config = GetDefaultAudioDeviceConfiguration();
    auto ac = lab::MakeRealtimeAudioContext(config.second,config.first);
    return ac;
}

std::unique_ptr<lab::AudioContext> makeOfflineAudioContext() {
    AudioStreamConfig config;
    config.desired_samplerate = 44100;
    config.desired_channels = 2;
    config.device_index = 1;
    auto ac = lab::MakeOfflineAudioContext(config,500);
    return ac;
}
