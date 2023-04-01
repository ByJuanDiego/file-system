cmake_minimum_required(VERSION 3.24)
project(file_system)

set(CMAKE_CXX_STANDARD 20)

add_executable(file_system src/main.cpp inc/struct/alumno1.hpp inc/fixedrecord.hpp inc/p1.h inc/p2.h inc/p3.h inc/p4.h inc/func/read.hpp)
