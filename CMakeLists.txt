cmake_minimum_required(VERSION 3.27)
project(2proj_AED_G106)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/definition)
include_directories(src/header)

add_executable(2proj_AED_G106
        src/definition/Airline.cpp
        src/definition/Airport.cpp
        src/definition/Flight.cpp
        src/definition/Graph.cpp
        src/definition/Loader.cpp
        src/definition/Menu.cpp
        src/header/Airline.h
        src/header/Airport.h
        src/header/Flight.h
        src/header/Graph.h
        src/header/Loader.h
        src/header/Menu.h
        main.cpp)
