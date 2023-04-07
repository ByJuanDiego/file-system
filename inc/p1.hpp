//
// Created by juandiego on 3/31/23.
//

#ifndef FILE_SYSTEM_P1_HPP
#define FILE_SYSTEM_P1_HPP

#include <vector>
#include <limits>
#include <utility>
#include <sstream>
#include <cstring>
#include <fstream>
#include <iostream>

#include "func/read.hpp"

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
    };

    const int record_size = sizeof(p1::student);

    std::ostream &operator<<(std::ostream &stream, p1::student &p) {
        stream << p.code << " " << p.name << " " << p.last_name << " " << p.career << "\n";
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

    class fixed_record {

        std::fstream file;
        std::string file_name;

        inline long number_of_records() {
            file.seekg(0, std::ios::end);
            long file_size = file.tellg();
            file.seekg(0);
            return (file_size) / (p1::record_size);
        }

    public:
        explicit fixed_record(std::string file_name);

        ~fixed_record();

        std::vector<p1::student> load();

        void add(p1::student &record);

        p1::student read_record(int pos);
    };

    fixed_record::fixed_record(std::string file_name) : file_name(std::move(file_name)) {
    }

    fixed_record::~fixed_record() = default;

    std::vector<p1::student> fixed_record::load() {
        file.open(file_name, std::ios::in);
        std::vector<p1::student> records;
        long n_records = number_of_records();

        if (file.is_open()) {
            for (int i = 0; i < n_records; ++i) {
                p1::student record{};
                file >> record;
                records.push_back(record);
            }
        }

        file.close();
        return records;
    }

    void fixed_record::add(p1::student &record) {
        file.open(file_name, std::ios::app);

        if (file.is_open()) {
            file << record;
            file.close();
        } else {
            std::cerr << "Cannot open the file\n";
        }
    }

    p1::student fixed_record::read_record(int pos) {
        file.open(file_name, std::ios::in);
        p1::student student{};

        long max_pos = number_of_records() - 1;
        if (pos > max_pos || pos < 0) {
            throw std::invalid_argument("invalid position");
        }

        file.seekg(p1::record_size * pos);
        file >> student;

        file.close();
        return student;
    }

    void test(const std::string &file_name) {
        p1::fixed_record fr(file_name);

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
                    p1::student student{};
                    p1::init(student);
                    fr.add(student);
                    break;
                }

                case 1 : {
                    std::vector<p1::student> records = fr.load();
                    for (p1::student &student: records) {
                        std::cout << to_string(student) << std::endl;
                    }
                    break;
                }

                case 2 : {
                    int position;
                    std::cout << "Enter the record position: ";
                    std::cin >> position;
                    p1::student student = fr.read_record(position);
                    std::cout << "The [" << position << "] student is: " << to_string(student) << std::endl;
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

#endif //FILE_SYSTEM_P1_HPP
