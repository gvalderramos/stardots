cmake_minimum_required(VERSION 3.27)
project(nodalAlgorithm)

set(CMAKE_CXX_STANDARD 17 REQUIRED)

add_subdirectory(lib)
add_subdirectory(src)

add_subdirectory(tests)