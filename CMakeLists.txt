cmake_minimum_required(VERSION 3.13)
project(LAG)

set(CMAKE_CXX_STANDARD 14)

add_executable(LAG main.cpp utils/utils.cpp utils/utils.h TokenRecognizer/TokenRecognizer.cpp TokenRecognizer/TokenRecognizer.h)