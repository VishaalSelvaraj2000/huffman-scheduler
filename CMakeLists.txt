cmake_minimum_required(VERSION 3.15)

project(huffman-scheduler LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

add_executable(scheduler
        scheduler.h
        scheduler.cpp
        fgk.h
        fgk.cpp
        main.cpp)