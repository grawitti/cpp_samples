cmake_minimum_required(VERSION 3.10)

project(main VERSION 0.2)

configure_file(ntp.conf.in ntp.conf)

add_executable(${PROJECT_NAME} replace_str_in_file.cpp)
