cmake_minimum_required(VERSION 3.20)

project(DrumMachine VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++20")

find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})

# include_directories(/opt/homebrew/Cellar/portaudio/19.7.0/include)

add_executable(DrumMachine ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/instrument_picker.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/transport.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/volume_control.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/string_constants.cpp)

target_include_directories(DrumMachine PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(DrumMachine ${wxWidgets_LIBRARIES})
# target_link_libraries(DrumMachine /opt/homebrew/Cellar/portaudio/19.7.0/lib/libportaudio.2.dylib)

set_target_properties(DrumMachine
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/")

