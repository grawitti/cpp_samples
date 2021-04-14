cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDART 11)
set(CMAKE_CXX_STANDART_REQUIRED True)

project(gtest_sample)

add_executable(gtest_sample tests.cpp)
target_link_libraries(gtest_sample PRIVATE gtest gtest_main pthread)
