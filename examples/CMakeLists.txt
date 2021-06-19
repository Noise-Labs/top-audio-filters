cmake_minimum_required(VERSION 3.17)
project(chord_detection)
set(CMAKE_CXX_STANDARD 20)
include_directories(/usr/local/include)
set(CMAKE_XCODE_ATTRIBUTE_FRAMEWORK_SEARCH_PATHS /usr/local/lib)
link_directories(/usr/local/lib /Users/miskolee/develop/src/noiselabs/top-audio-filters)

add_executable(example main.cpp)
target_link_libraries(example

        top_audio_filters
        "libnyquist"
        "samplerate"
        "wavpack"
        "LabSound"
        "-framework Accelerate"
        "-framework Cocoa"
        "-framework CoreAudio"
        "-framework AudioUnit"
        "-framework AudioToolbox"
        )
