cmake_minimum_required(VERSION 4.0)
project(resourceMonitoring)

set(CMAKE_CXX_STANDARD 20)

add_executable(resourceMonitoring main.cpp
        cpu.cpp
        cpu.h)
