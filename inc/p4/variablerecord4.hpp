//
// Created by juandiego on 4/4/23.
//

#ifndef FILE_SYSTEM_VARIABLERECORD4_HPP
#define FILE_SYSTEM_VARIABLERECORD4_HPP

#include <string>
#include <vector>
#include <fstream>
#include "tuition.hpp"

namespace p4 {

    class variable_record {
    private:
        std::fstream data_file;
        std::fstream index_file;

        std::string data_file_name;
        std::string index_file_name;

    public:
        explicit variable_record(std::string data_file_name, std::string index_file_name);

        std::vector<p4::tuition> load();

        void add(p4::tuition &record);

        p4::tuition read_record(int pos);
    };

    variable_record::variable_record(std::string data_file_name, std::string index_file_name)
            : data_file_name(std::move(data_file_name)),
              index_file_name(std::move((index_file_name))) {}

    std::vector<p4::tuition> variable_record::load() {
        index_file.open(index_file_name, std::ios::in | std::ios::binary);
        data_file.open(data_file_name, std::ios::in | std::ios::binary);

        std::vector<p4::tuition> records;

        if (!index_file.is_open() || !data_file.is_open()) {
            index_file.close();
            data_file.close();
            return records;
        }

        int i_pos = 0;

        while (!index_file.eof()) {
            p4::tuition record;

            index_file.read((text) &i_pos, int_sz);
            if (index_file.fail()) {
                break;
            }

            /// Set the file pointer to the current record position
            data_file.seekg(i_pos);

            /// Internally assigns the values of the record in memory
            p4::read(record, data_file);

            records.push_back(record);
        }

        index_file.close();
        data_file.close();
        return records;
    }

    void variable_record::add(tuition &record) {
        index_file.open(index_file_name, std::ios::app | std::ios::binary);
        data_file.open(data_file_name, std::ios::app | std::ios::binary);

        if (!index_file.is_open() || !data_file.is_open()) {
            index_file.close();
            data_file.close();
            return;
        }

        /// Assigns the position of the record
        int pos = (int) data_file.tellg();

        /// Writes the beginning position of the record in the index file
        index_file.write((text) &pos, int_sz);

        /// Writes the record in the data file
        data_file << record;

        index_file.close();
        data_file.close();
    }

    p4::tuition variable_record::read_record(int pos) {
        if (pos < 0) {
            throw std::invalid_argument("invalid position");
        }

        index_file.open(index_file_name, std::ios::in | std::ios::binary);
        data_file.open(data_file_name, std::ios::in | std::ios::binary);

        /// Sets the index pointer to the `pos` times `int_sz` value
        index_file.seekg(pos * int_sz);

        int record_pos;
        /// Reads the value of the record position at data file
        index_file.read((text) &record_pos, int_sz);

        if (index_file.fail()) {
            throw std::invalid_argument("invalid position");
        }

        /// Sets the data file pointer to the beginning of the record at `pos`
        data_file.seekg(record_pos);

        p4::tuition record;
        /// Reads the record information
        p4::read(record, data_file);

        index_file.close();
        data_file.close();

        return record;
    }
}

#endif //FILE_SYSTEM_VARIABLERECORD4_HPP
