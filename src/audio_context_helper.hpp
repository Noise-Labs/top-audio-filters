#ifndef  TOP_AUDIO_FILTER_AUDIO_CONTEXT_HELPER_H
#define TOP_AUDIO_FILTER_AUDIO_CONTEXT_HELPER_H

#include <LabSound/LabSound.h>

std::unique_ptr<lab::AudioContext> makeRealTimeAudioContext();
std::unique_ptr<lab::AudioContext> makeOfflineAudioContext();

#endif