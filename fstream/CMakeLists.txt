cmake_minimum_required(VERSION 3.10)

project(fstream VERSION 0.2)

configure_file(test.txt.in test.txt)

add_executable(${PROJECT_NAME} fstream.cpp)
