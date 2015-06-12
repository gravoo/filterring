cmake_minimum_required(VERSION 3.2)
project(kwantyzacja)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Image.h Image.cpp Pixel.cpp Pixel.h FileReader.cpp FileWriter.cpp FileReader.h FileWriter.h)
add_executable(kwantyzacja ${SOURCE_FILES})
# Quantizer.cpp Quantizer.h QuantizerEncoder.cpp
# QuantizerEncoder.h QuantizerDecoder.cpp QuantizerDecoder.h)
################################
# GTest
################################
ADD_SUBDIRECTORY (gtest-1.7.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

################################
# Unit Tests
################################
# Add test cpp file
add_executable( runUnitTests gTest.cpp Image.h Image.cpp Pixel.cpp Pixel.h FileReader.cpp
FileWriter.cpp FileReader.h FileWriter.h Quantizer.cpp Quantizer.h QuantizerEncoder.h
 QuantizerEncoder.cpp QuantizerEncoder.h QuantizerDecoder.cpp QuantizerDecoder.h)
# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests gtest gtest_main)
add_test( runUnitTests runUnitTests )