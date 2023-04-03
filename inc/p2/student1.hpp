//
// Created by juandiego on 3/31/23.
//

#ifndef FILE_SYSTEM_STUDENT1_HPP
#define FILE_SYSTEM_STUDENT1_HPP

#include <iostream>
#include <sstream>
#include <stddef.h>
#include <limits>
#include <cstring>
#include <fstream>

#include "../func/read.hpp"

namespace p1 {

    constexpr int code_length = 5;
    constexpr int name_length = 11;
    constexpr int last_name_length = 20;
    constexpr int career_length = 15;

    struct student {
        char code[code_length];
        char name[name_length];
        char last_name[last_name_length];
        char career[career_length];
        int ciclo;
        float mensualidad;
        student *next;
    };

    const int record_size = sizeof(p1::student);

    std::ostream &operator<<(std::ostream &stream, p1::student &p) {
        stream << p.code << " " << p.name << " " << p.last_name << " " << p.career <<  p.ciclo << p.mensualidad  <<"\n";
        stream << std::flush;
        return stream;
    }

    std::istream &operator>>(std::istream &stream, p1::student &p) {
        stream.read(p.code, code_length);
        p.code[code_length - 1] = '\0';

        stream.read(p.name, name_length);
        p.name[name_length - 1] = '\0';

        stream.read(p.last_name, last_name_length);
        p.last_name[last_name_length - 1] = '\0';

        stream.read(p.career, career_length);
        p.career[career_length - 1] = '\0';
        return stream;
    }

    void init(p1::student &student) {
        std::cout << "======= Student Information =======" << std::endl;
        std::cout << "Code: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

        read_from_console(student.code, code_length);
        std::cout << "Name: ";
        read_from_console(student.name, name_length);
        std::cout << "Last name: ";
        read_from_console(student.last_name, last_name_length);
        std::cout << "Career: ";
        read_from_console(student.career, career_length);
    }

    std::string to_string(p1::student &student) {
        std::stringstream ss;
        ss << "(" << student.code << ", " << student.name << ", " << student.last_name << ", " << student.career << ")";
        return ss.str();
    }
}

#endif //FILE_SYSTEM_STUDENT1_HPP
