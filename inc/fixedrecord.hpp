//
// Created by juandiego on 3/31/23.
//

#ifndef FILE_SYSTEM_FIXEDRECORD_HPP
#define FILE_SYSTEM_FIXEDRECORD_HPP

#include <fstream>
#include <utility>
#include <vector>

#include "./struct/alumno1.hpp"

class FixedRecord {
private:

    std::ifstream input_file;
    std::ofstream output_file;
    std::string file_name;

public:
    explicit FixedRecord(std::string file_name) : file_name(std::move(file_name)) {
    }

    ~FixedRecord() = default;

    std::vector<p1::Alumno> load() {

    }

    void add(p1::Alumno record) {

    }

    p1::Alumno readRecord(int pos) {

    }
};

#endif //FILE_SYSTEM_FIXEDRECORD_HPP
