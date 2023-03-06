cmake_minimum_required(VERSION 3.10)
project(Microwave)

set(CMAKE_CXX_STANDARD 14)

include_directories(product)

add_subdirectory(product)
add_subdirectory(test)
add_subdirectory(lib/googletest)