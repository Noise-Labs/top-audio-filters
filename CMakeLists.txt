cmake_minimum_required(VERSION 3.17)
project(top_audio_filters CXX)
set(CMAKE_XCODE_ATTRIBUTE_FRAMEWORK_SEARCH_PATHS /usr/local/lib)
set(CMAKE_C_STANDARD 03)
set(CMAKE_CXX_STANDARD 11)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
include_directories(/usr/local/include)
include_directories(src)
link_directories(/usr/local/lib)
aux_source_directory(src SOURCE)
add_library(top_audio_filters SHARED ${SOURCE})
set(TARGET top_audio_filters PROPERTY POSITION_INDEPENDENT_CODE ON)

INSTALL(TARGETS top_audio_filters
        DESTINATION "lib"
        )

target_link_libraries(top_audio_filters
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