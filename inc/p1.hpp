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

    /// Student definition
    struct student {
        char code[code_length];
        char name[name_length];
        char last_name[last_name_length];
        char career[career_length];
    };

    const int record_size = sizeof(p1::student);

    /// Writes the student `record` in `stream`
    std::ostream &operator<<(std::ostream &stream, p1::student &record) {
        stream << record.code << " " << record.name << " " << record.last_name << " " << record.career << "\n";
        stream << std::flush;
        return stream;
    }

    /// Loads a student from a file to memory and stores it in `record`
    std::istream &operator>>(std::istream &stream, p1::student &record) {
        stream.read(record.code, code_length);
        record.code[code_length - 1] = '\0';

        stream.read(record.name, name_length);
        record.name[name_length - 1] = '\0';

        stream.read(record.last_name, last_name_length);
        record.last_name[last_name_length - 1] = '\0';

        stream.read(record.career, career_length);
        record.career[career_length - 1] = '\0';
        return stream;
    }

    /// Initializes `student` in memory
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

    /// Format `student` to a human readable format
    std::string to_string(p1::student &student) {
        std::stringstream ss;
        ss << "("
           << student.code << ", "
           << student.name << ", "
           << student.last_name << ", "
           << student.career
           << ")";
        return ss.str();
    }

    /** Class in charge of manipulate `p1::student` struct
     *
     * This class allows to write, read an load `p1::student` records.
     */
    class fixed_record {

        std::fstream file;          /// File instance that contains `p1::student` data
        std::string file_name;      /// The name of the file

        /// Get the total number of records in `file`
        inline long number_of_records() {
            file.seekg(0, std::ios::end);
            long file_size = file.tellg();
            file.seekg(0);
            return (file_size) / (p1::record_size);
        }

    public:
        explicit fixed_record(std::string file_name);

        ~fixed_record();

        /// Loads all the records in memory
        std::vector<p1::student> load();

        /// Writes a new record in a disk `file`
        void add(p1::student &record);

        /// Load the `pos` record in memory and return it
        p1::student read_record(int pos);
    };

    // test function, internally, instantiates a `p1::fixed_record` and use it to manipulate a disk file
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


// Definition of public member functions of `p1::fixed_record`
namespace p1 {
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
}

#endif //FILE_SYSTEM_P1_HPP
