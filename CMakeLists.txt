cmake_minimum_required(VERSION 3.24)
project(file_system)

set(CMAKE_CXX_STANDARD 20)

add_executable(file_system
        src/main.cpp
        inc/p1.hpp
        inc/p2.hpp
        inc/func/read.hpp
        inc/p3.hpp
        inc/p4.hpp
        inc/global.hpp)
