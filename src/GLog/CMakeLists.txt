cmake_minimum_required(VERSION 3.15)
project(GLog-Library CXX)

file(GLOB SOURCES "*.cpp")
add_library(GLog STATIC ${SOURCES})
target_include_directories(GLog PRIVATE ../../include)
