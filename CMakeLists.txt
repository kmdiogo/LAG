cmake_minimum_required(VERSION 3.13)
project(LAG)

set(CMAKE_CXX_STANDARD 14)

add_executable(LAG main.cpp utils/utils.cpp utils/utils.h TokenReturner/TokenReturner.cpp TokenReturner/TokenReturner.h Parser/Parser.cpp Parser/Parser.h ParseTreeNode/ParseTreeNode.cpp ParseTreeNode/ParseTreeNode.h NFAGenerator/NFAGenerator.cpp NFAGenerator/NFAGenerator.h NFANode/NFANode.h NFANode/NFANode.cpp)