//
// Created by juandiego on 4/1/23.
//

#ifndef FILE_SYSTEM_Q3_HPP
#define FILE_SYSTEM_Q3_HPP

#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

namespace p3 {

    /// Student definition
    struct student {
        std::string name;
        std::string last_name;
        std::string career;
        float monthly_payment{};
    };

    /// Initializes a `p3::student`
    void init(p3::student &student);

    /// Writes the student `record` in `stream`
    std::ostream &operator<<(std::ostream &stream, p3::student &record);

    /// Loads a student from a file to memory and stores it in `record`
    std::istream &operator>>(std::istream &stream, p3::student &record);

    /// Format `student` to a human readable format
    std::string to_string(p3::student &student);

    /** Class in charge of manipulate `p3::student` struct
     *
     * This class allows to write, read an load `p3::student` records.
     * The records are delimited by '\n' and this fields by a '|'
     */
    class variable_record {
    private:
        std::fstream file;
        std::string file_name;

    public:
        explicit variable_record(std::string file_name);

        ~variable_record();

        /// Loads all the records in memory
        std::vector<p3::student> load();

        /// Writes a new record in a disk `file`
        void add(p3::student &record);

        /// Load the `pos` record in memory and return it
        p3::student read_record(int pos);
    };

    // test function, internally, instantiates a `p3::variable_record` and use it to manipulate a disk file
    void test(const std::string &file_name);
}

/// Definitions of functions related to `p3::student` struct manipulation
namespace p3 {
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

    std::ostream &operator<<(std::ostream &stream, p3::student &record) {
        stream << record.name << "|" << record.last_name << "|" << record.career << "|" << record.monthly_payment
               << "\n";
        stream << std::flush;
        return stream;
    }

    std::istream &operator>>(std::istream &stream, p3::student &record) {
        /// When the end of the file is reached, `stream.fail()` will equal `true` after reading `p.name`.
        /// Then, the `file >> record` will be casted as `false` and the loop breaks.
        std::getline(stream, record.name, '|');
        std::getline(stream, record.last_name, '|');
        std::getline(stream, record.career, '|');

        std::string payment;
        std::getline(stream, payment, '\n');
        record.monthly_payment = (stream.fail()) ? 0.0f : std::stof(payment);

        return stream;
    }

    std::string to_string(p3::student &student) {
        std::stringstream ss;
        ss << "("
           << student.name << ", "
           << student.last_name << ", "
           << student.career << ", "
           << student.monthly_payment
           << ")";
        return ss.str();
    }
}

/// Definition of public member functions of `p3::variable_record`
namespace p3 {
    variable_record::variable_record(std::string file_name) : file_name(std::move(file_name)) {
    }

    variable_record::~variable_record() = default;

    void variable_record::add(p3::student &record) {
        file.open(file_name, std::ios::app);
        if (!file.is_open()) {
            throw std::runtime_error(file_not_open);
        }

        // Writes the `record` information in the disk file
        file << record;

        file.close();
    }

    std::vector<p3::student> variable_record::load() {
        file.open(file_name, std::ios::in);
        if (!file.is_open()) {
            throw std::runtime_error(file_not_open);
        }

        std::vector<p3::student> records;
        std::string line;
        /// Ignore fields line
        std::getline(file, line, '\n');
        p3::student record;

        /// https://en.cppreference.com/w/cpp/io/basic_ios/operator_bool
        /// Fields values are assigned using the current line
        while (file >> record) {
            records.push_back(record);
        }

        file.close();
        return records;
    }

    p3::student variable_record::read_record(int pos) {
        /// Verifies `pos`
        if (pos < 0) {
            throw std::invalid_argument(not_valid_position);
        }

        file.open(file_name, std::ios::in);
        if (!file.is_open()) {
            throw std::runtime_error(file_not_open);
        }

        int i = 0;
        /// Ignores the first `pos+1` records (including the fields line, that's the reason for `+1`)
        for (; (i < (pos + 1)) && file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); ++i);
        /// If the `pos + 1` cannot be reached, it means that the file cannot read more lines;
        /// then, the position is not valid
        if (i != (pos + 1)) {
            file.close();
            throw std::invalid_argument(not_valid_position);
        }

        p3::student record{};
        /// Reads the record information
        file >> record;

        file.close();
        return record;
    }
}

/// Definition of test function
namespace p3 {
    void test(const std::string &file_name) {
        p3::variable_record vr(file_name);
        std::system(clear_console);

        do {
            std::cout << menu_1 << std::endl;
            int option;
            do {
                std::cout << "Select an option: ";
                std::cin >> option;
            } while (option < 0 || option > 3);
            std::cout << std::endl;

            switch (option) {
                case 0 : {
                    p3::student student{};
                    p3::init(student);
                    try {
                        vr.add(student);
                    } CATCH
                    std::cout << "The new record has been successfully written in disk" << std::endl;
                    break;
                }
                case 1 : {
                    try {
                        std::vector<p3::student> records = vr.load();
                        for (p3::student &student: records) {
                            std::cout << to_string(student) << std::endl;
                        }
                    } CATCH
                    break;
                }
                case 2 : {
                    int position;
                    std::cout << "Enter the record position: ";
                    std::cin >> position;
                    try {
                        p3::student student = vr.read_record(position);
                        std::cout << "The [" << position << "] student is: " << to_string(student) << std::endl;
                    } CATCH
                    break;
                }
                default: {
                    std::system(clear_console);
                    return;
                }
            }

            std::cout << std::endl << "Press Enter to continue..." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            std::system(clear_console);

        } while (true);
    }
}

#endif //FILE_SYSTEM_Q3_HPP
