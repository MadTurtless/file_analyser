cmake_minimum_required(VERSION 4.0)
project(file_analyser)

set(CMAKE_CXX_STANDARD 20)

add_executable(file_analyser src/main.cpp
        src/File.cpp
        include/File.h
)
