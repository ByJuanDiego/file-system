//
// Created by juandiego on 4/1/23.
//

#ifndef FILE_SYSTEM_P3_HPP
#define FILE_SYSTEM_P3_HPP

#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

namespace p3 {

    struct student {
        std::string name;
        std::string last_name;
        std::string career;
        float monthly_payment{};
    };

    void init(p3::student &student) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "======= Student Information =======" << std::endl;

        std::cout << "Name: ";
        std::getline(std::cin, student.name);

        std::cout << "Last name: ";
        std::getline(std::cin, student.last_name);

        std::cout << "Career: ";
        std::getline(std::cin, student.career);

        std::cout << "Monthly payment: ";
        std::cin >> student.monthly_payment;
    }

    std::ostream &operator<<(std::ostream &stream, p3::student &p) {
        stream << p.name << "|" << p.last_name << "|" << p.career << "|" << p.monthly_payment << "\n";
        stream << std::flush;
        return stream;
    }

    std::istream &operator>>(std::istream &stream, p3::student &p) {
        /// When the end of the file is reached, `stream.fail()` will equal `true` after reading `p.name`.
        /// Then, the `file >> record` will be casted as `false` and the loop breaks.
        std::getline(stream, p.name, '|');
        std::getline(stream, p.last_name, '|');
        std::getline(stream, p.career, '|');

        std::string payment;
        std::getline(stream, payment, '\n');
        p.monthly_payment = (stream.fail()) ? 0.0f : std::stof(payment);

        return stream;
    }

    std::string to_string(p3::student &student) {
        std::stringstream ss;
        ss << "(" << student.name << ", " << student.last_name << ", " << student.career << ", "
           << student.monthly_payment << ")";
        return ss.str();
    }

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
            p3::student record;

            /// https://en.cppreference.com/w/cpp/io/basic_ios/operator_bool
            /// Fields values are assigned using the current line
            while (file >> record) {
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

            /// Ignores the first `pos+1` records (including the fields line, that's the reason for `+1`)
            for (; (i < (pos + 1)) && file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); ++i);
            /// If the `pos + 1` cannot be reached, it means that the file cannot read more lines;
            /// then, the position is not valid
            if (i != (pos + 1)) {
                throw std::invalid_argument("invalid position");
            }

            file >> record;
        }

        file.close();
        return record;
    }

    void test(const std::string &file_name) {
        p3::variable_record vr(file_name);

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
                    p3::student student{};
                    p3::init(student);
                    vr.add(student);
                    break;
                }

                case 1 : {
                    std::vector<p3::student> records = vr.load();
                    for (p3::student &student: records) {
                        std::cout << to_string(student) << std::endl;
                    }
                    break;
                }

                case 2 : {
                    int position;
                    std::cout << "Enter the record position: ";
                    std::cin >> position;
                    p3::student student = vr.read_record(position);
                    std::cout << "The [" << position << "] student is: " << to_string(student) << std::endl;
                    break;
                }
                default: {
                    std::system("clear");
                    return;
                }
            }

            std::cout << std::endl << "Press Enter to continue..." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            std::system("clear");

        } while (true);

    }
}

#endif //FILE_SYSTEM_P3_HPP
