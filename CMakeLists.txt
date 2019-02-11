cmake_minimum_required(VERSION 3.13)
project(LAG)

set(CMAKE_CXX_STANDARD 14)

add_executable(LAG main.cpp token_recognizers/token_recognizers.cpp utils/utils.cpp utils/utils.h token_recognizers/token_recognizers.h)