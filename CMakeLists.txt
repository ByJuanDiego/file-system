cmake_minimum_required(VERSION 3.24)
project(file_system)

set(CMAKE_CXX_STANDARD 20)

add_executable(file_system
        src/main.cpp
        inc/tests/q1.hpp
        inc/tests/q2.hpp
        inc/tests/q3.hpp
        inc/tests/q4.hpp
        inc/utils/read.hpp
        inc/utils/global.hpp)
