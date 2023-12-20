cmake_minimum_required(VERSION 3.26)
project(2proj_AED_G106 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(src)
include_directories(src/header)

add_executable(2proj_AED_G106
        src/header/Graph.h)
