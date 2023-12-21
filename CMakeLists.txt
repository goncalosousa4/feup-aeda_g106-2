cmake_minimum_required(VERSION 3.26)
project(2projAED)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(src)
include_directories(src/header)

add_executable(2projAED
        src/header/Graph.h)
cmake_minimum_required(VERSION 3.26)
project(2projAED)

set(CMAKE_C_STANDARD 11)

# Add your source files
set(SOURCE_FILES
        src/main.c
        src/file1.c
        src/file2.c
        # Add more source files as needed
)

# Add include directories
include_directories(.)
include_directories(src)
include_directories(src/header)

# Create the executable
add_executable(2projAED ${SOURCE_FILES})
