cmake_minimum_required(VERSION 3.12.2)

project(cpack_test)

add_executable(test main.cpp)

SET(CPACK_GENERATOR "DEB")
SET(CPACK_PACKAGE_CONTACT "TEST")
INCLUDE(CPack)

