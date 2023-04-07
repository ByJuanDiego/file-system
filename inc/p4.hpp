//
// Created by juandiego on 4/4/23.
//

#ifndef FILE_SYSTEM_P4_HPP
#define FILE_SYSTEM_P4_HPP

#include <string>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include <iostream>

#include "global.hpp"

namespace p4 {

    struct tuition {
        std::string code;
        int cycle{};
        float monthly_payment{};
        std::string observations;
    };

    void init(p4::tuition &tuition) {
        std::cout << "======= Tuition Information =======" << std::endl;

        std::cout << "Code: ";
        std::cin >> tuition.code;

        std::cout << "Current cycle: ";
        std::cin >> tuition.cycle;

        std::cout << "Monthly payment: ";
        std::cin >> tuition.monthly_payment;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Observations: ";
        std::getline(std::cin, tuition.observations);
    }

    void read(p4::tuition &record, std::fstream &stream) {
        int n_code_bytes, n_observations_bytes;

        /// Reading the code length
        stream.read((text) &n_code_bytes, int_sz);

        char *code = new char[n_code_bytes + 1];
        /// Reading the code
        stream.read(code, n_code_bytes);
        code[n_code_bytes] = '\0';
        record.code = code;
        delete[] code;

        /// Reading the cycle
        stream.read((text) &record.cycle, int_sz);

        /// Reading the monthly payment
        stream.read((text) &record.monthly_payment, int_sz);

        /// Reading the observations length
        stream.read((text) &n_observations_bytes, int_sz);

        char *observations = new char[n_observations_bytes + 1];
        /// Reading the observations
        stream.read(observations, n_observations_bytes);
        observations[n_observations_bytes] = '\0';
        record.observations = observations;
        delete[] observations;
    }

    std::string to_string(p4::tuition &record) {
        std::stringstream ss;
        ss << "("
           << record.code << ", "
           << record.cycle << ", "
           << record.monthly_payment << ", "
           << record.observations
           << ")";
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &stream, p4::tuition &record) {
        int code_length = (int) record.code.length();
        int observations_length = (int) record.observations.length();

        /// Writing the code length (variable length)
        stream.write((text) &code_length, int_sz);
        stream.write((text) record.code.c_str(), code_length);

        /// Writing the current cycle
        stream.write((text) &record.cycle, int_sz);

        /// Writing the monthly payment
        stream.write((text) &record.monthly_payment, float_sz);

        /// Writing the observations (variable length)
        stream.write((text) &observations_length, int_sz);
        stream.write((text) record.observations.c_str(), observations_length);

        return stream;
    }


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

    void test(const std::string &data_file, const std::string &header_file) {
        p4::variable_record vr(data_file, header_file);

        do {
            int option;

            std::cout << std::endl;
            std::cout << "============== Menu ==============" << std::endl;
            std::cout << "Options " << std::endl;
            std::cout << "    [0]: Add a new record" << std::endl;
            std::cout << "    [1]: Read all records" << std::endl;
            std::cout << "    [2]: Read the ith record" << std::endl;
            std::cout << "    [3]: Exit" << std::endl;
            std::cout << std::endl;

            do {
                std::cout << "Select an option: ";
                std::cin >> option;
            } while (option < 0 || option > 3);
            std::cout << std::endl;

            switch (option) {
                case 0 : {
                    p4::tuition tuition{};
                    p4::init(tuition);
                    vr.add(tuition);
                    break;
                }

                case 1 : {
                    std::vector<p4::tuition> records = vr.load();
                    for (p4::tuition &tuition: records) {
                        std::cout << to_string(tuition) << std::endl;
                    }
                    break;
                }

                case 2 : {
                    int position;
                    std::cout << "Enter the record position: ";
                    std::cin >> position;
                    p4::tuition student = vr.read_record(position);
                    std::cout << "The [" << position << "] student is: " << p4::to_string(student) << std::endl;
                    break;
                }

                default: {
                    std::system("clear");
                    return;
                }
            }

            std::cout << std::endl << "Press Enter to continue..." << std::endl;
            if (option != 0) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cin.get();
            std::system("clear");

        } while (true);
    }
}

#endif //FILE_SYSTEM_P4_HPP
