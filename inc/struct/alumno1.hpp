//
// Created by juandiego on 3/31/23.
//

#ifndef FILE_SYSTEM_ALUMNO1_HPP
#define FILE_SYSTEM_ALUMNO1_HPP

#include <cstring>
#include <iostream>
#include <fstream>

#include "../func/read.hpp"

namespace p1 {

    constexpr int code_length = 5;
    constexpr int name_length = 11;
    constexpr int last_name_length = 20;
    constexpr int career_length = 15;

    struct Alumno {
        char codigo[code_length + 1];
        char nombre[name_length + 1];
        char apellidos[last_name_length + 1];
        char carrera[career_length + 1];

        void init();
        void append_to_file(const std::string &file_name);
    };

    std::ostream &operator<<(std::ostream &stream, p1::Alumno &p) {
        stream << p.codigo;
        stream << p.nombre;
        stream << p.apellidos;
        stream << p.carrera;
        stream << "\n";
        stream << std::flush;
        return stream;
    }

    std::istream &operator>>(std::istream &stream, p1::Alumno &p) {
        stream.get(p.codigo, code_length);
        stream.get(p.nombre, name_length);
        stream.get(p.apellidos, last_name_length);
        stream.get(p.carrera, career_length);
        stream.get();
        return stream;
    }

    void Alumno::init() {
        std::cout << "Codigo: ";
        readFromConsole(codigo, code_length + 1);
        std::cout << "Nombre: ";
        readFromConsole(nombre, name_length + 1);
        std::cout << "Apellidos: ";
        readFromConsole(apellidos, last_name_length + 1);
        std::cout << "Carrera: ";
        readFromConsole(carrera, career_length + 1);
    }

    void Alumno::append_to_file(const std::string &file_name)  {
        std::ofstream out;
        out.open(file_name, std::ios::app);
        if (out.is_open()) {
            out << *this;
            out.close();
        } else {
            std::cerr << "Cannot open the file\n";
        }
    }
}

#endif //FILE_SYSTEM_ALUMNO1_HPP
