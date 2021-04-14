cmake_minimum_required(VERSION 3.10)

# Set the prokect name
project(Tutorial VERSION 1.0)

configure_file(TutorialConfig.h.in TutorialConfig.h)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(Tutorial tutorial.cxx)

target_include_directories(Tutorial PUBLIC
							"${PROJECT_BINARY_DIR}"
							)
