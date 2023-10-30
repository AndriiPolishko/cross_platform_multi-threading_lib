cmake_minimum_required(VERSION 3.24)
project(my_thread)
set(PROJECT_NAME my_thread)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable( ${PROJECT_NAME}
        include/my_thread.h
        src/my_thread.cpp
        main.cpp portable_types/portable_thread.h include/my_mutex.h src/my_mutex.cpp portable_types/portable_mutex.h)

target_link_libraries( ${PROJECT_NAME} PRIVATE -pthread)