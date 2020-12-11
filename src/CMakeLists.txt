cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

file(GLOB lib_SRC "*.cpp")

target_sources(${Target} PRIVATE ${lib_SRC})
