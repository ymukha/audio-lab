cmake_minimum_required(VERSION 3.20)

project(fir_q15
        VERSION 0.1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)

add_executable(fir_basics
               src/main.cpp
               src/AudioUtils.cpp
               src/FIR.cpp)

target_include_directories(fir_basics
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)