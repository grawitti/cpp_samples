cmake_minimum_required(VERSION 3.7.0)

set(DBUS_INCLUDE_DIRS "/usr/include/dbus-1.0;/usr/lib/x86_64-linux-gnu/dbus-1.0/include/usr/include/dbus-1.0;/usr/lib/x86_64-linux-gnu/dbus-1.0/include")

project(dbus_samples)

add_executable(${CMAKE_PROJECT_NAME} dbus_sample.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
                      dbus-1)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${DBUS_INCLUDE_DIRS})
