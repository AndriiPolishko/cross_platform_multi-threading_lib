cmake_minimum_required(VERSION 3.26)
project(cross_platform_multi_threading_lib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(cross_platform_multi_threading_lib
        include/my_thread.h
        src/my_thread.cpp
        main.cpp)
