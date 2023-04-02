//
// Created by juandiego on 4/1/23.
//

#ifndef FILE_SYSTEM_VARIABLERECORD_HPP
#define FILE_SYSTEM_VARIABLERECORD_HPP

#include <vector>
#include <fstream>
#include "student.hpp"

namespace p3 {
    class variable_record {
    private:
        std::fstream file;
        std::string file_name;

    public:
        explicit variable_record(std::string file_name);

        std::vector<p3::student> load();

        void add(p3::student &record);

        p3::student read_record(int pos);
    };

    variable_record::variable_record(std::string file_name) : file_name(std::move(file_name)) {
    }

    void variable_record::add(p3::student &record) {
        file.open(file_name, std::ios::app);
        if (file.is_open()) {
            file << record;
            file.close();
        } else {
            std::cerr << "Cannot open the file\n";
        }
    }

    std::vector<p3::student> variable_record::load() {
        file.open(file_name, std::ios::in);
        std::vector<p3::student> records;
        std::string line;

        if (file.is_open()) {

            /// Ignore fields line
            std::getline(file, line, '\n');

            while (std::getline(file, line, '\n')) {
                p3::student record;
                /// Fields values are assigned using the current line
                p3::read(record, (char *) line.c_str());
                records.push_back(record);
            }
        }

        file.close();
        return records;
    }

    p3::student variable_record::read_record(int pos) {
        file.open(file_name, std::ios::in);
        p3::student record{};
        std::string line;

        if (pos < 0) {
            throw std::invalid_argument("invalid position");
        }

        if (file.is_open()) {

            int i = 0;

            /// Reads the first `pos+1` lines (including the fields line)
            for (; (i < (pos + 1)) && std::getline(file, line, '\n'); ++i);

            /// If the `pos + 1` cannot be reached, it means that the file cannot read more lines,
            /// then the position is not valid
            if (i != (pos + 1)) {
                throw std::invalid_argument("invalid position");
            }

            std::getline(file, line, '\n');
            p3::read(record, (char *) line.c_str());
        }

        file.close();
        return record;
    }
}

#endif //FILE_SYSTEM_VARIABLERECORD_HPP
