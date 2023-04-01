//
// Created by juandiego on 3/31/23.
//

#ifndef FILE_SYSTEM_P1_HPP
#define FILE_SYSTEM_P1_HPP

#include <iostream>
#include "./struct/alumno1.hpp"

void test1() {
    p1::Alumno alumno{};
    alumno.init();
    alumno.append_to_file("./data/datos1.txt");
}

#endif // FILE_SYSTEM_P1_HPP