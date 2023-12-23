cmake_minimum_required(VERSION 3.27)
project(2proj_AED_G106)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/definition)
include_directories(src/header)

add_executable(2proj_AED_G106
        src/definition/Airport.cpp
        src/definition/Loader.cpp
        src/header/Airport.h
        src/header/Graph.h
        src/header/Loader.h
        main.cpp
        src/definition/Graph.cpp)
