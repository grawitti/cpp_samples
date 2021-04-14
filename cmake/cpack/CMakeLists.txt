cmake_minimum_required(VERSION 3.7.2)

project(cpack_test)

add_executable(cpack_test main.cpp)

install(TARGETS cpack_test
	COMPONENT cpack_test
	RUNTIME DESTINATION "/home/"
	DESTINATION "/home/")

SET(CPACK_GENERATOR "DEB")
SET(CPACK_PACKAGE_CONTACT "CONTACTS")
INCLUDE(CPack)

