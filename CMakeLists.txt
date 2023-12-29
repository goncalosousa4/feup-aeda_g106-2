cmake_minimum_required(VERSION 3.26)
project(aaaaaaaaa)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/definition)
include_directories(src/header)

add_executable(aaaaaaaaa
        src/definition/Airport.cpp
        src/definition/Flight.cpp
        src/definition/Graph.cpp
        src/definition/Loader.cpp
        src/definition/Menu.cpp
        src/header/Airport.h
        src/header/Flight.h
        src/header/Graph.h
        src/header/Loader.h
        src/header/Menu.h
        main.cpp
        src/header/Airline.h
        src/definition/Airline.cpp)