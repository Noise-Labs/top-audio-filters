cmake_minimum_required(VERSION 3.17)
project(chord_detection)
set(CMAKE_CXX_STANDARD 20)
include_directories(/usr/local/include)
set(CMAKE_XCODE_ATTRIBUTE_FRAMEWORK_SEARCH_PATHS /usr/local/lib)

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
add_compile_options(-std=c++11 -pthread -g  -ggdb -O0 -Wall   -fstack-protector-all -march=native -fnon-call-exceptions)

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
