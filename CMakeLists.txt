cmake_minimum_required(VERSION 2.6)
project(RNDR)

set(CMAKE_CXX_COMPILER g++)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "build")

set(
  CMAKE_MODULE_PATH 
  "${CMAKE_INSTALL_PREFIX}/share/cmake-modules" ${CMAKE_MODULE_PATH})
 
# Put shared libraries in lib directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# C++14 is rad
set(CMAKE_CXX_FLAGS "-O0 -g -std=c++14 -Wall ${CMAKE_CXX_FLAGS}")

include_directories(.)

add_subdirectory(tests)
add_subdirectory(gfx)
add_subdirectory(etc)

enable_testing()

add_executable(test_gfx gfx_test.cpp)
target_link_libraries(test_gfx etc gfx)