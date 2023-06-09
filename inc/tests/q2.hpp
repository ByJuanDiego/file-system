#ifndef FILE_SYSTEM_Q2_HPP
#define FILE_SYSTEM_Q2_HPP

#include <fstream>
#include <utility>
#include <vector>
#include <sstream>
#include <limits>
#include <cstring>

#include "../utils/read.hpp"
#include "../utils/global.hpp"

namespace p2 {

    /// Const values
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

        int cycle;
        float monthly_payment;
    };

    /// Size of a `p2::student`
    const int record_size = sizeof(p2::student) - 1;

    /// Initializes a `p2::student`
    void init(p2::student &student);

    /// Writes the student `record` in `stream`
    void write(std::ostream &stream, p2::student &record, int &next_del);

    /// Loads a student from a file to memory and stores it in `record`
    void read(std::istream &stream, p2::student &record, int &next_del);

    /// Format `student` to a human readable format
    std::string to_string(p2::student &student);

    /** Class in charge of manipulate `p2::student` struct
     *
     * This class allows to write, read, load and delete `p2::student` records from a binary file.
     * Uses a implementation of `free-list` to delete a record logically.
     *
     *
     *                          Why in this case is it better to use a binary file?
     *
     *     • It allows us to store "variable length fields" that, in fact, have the same bytes length.
     *       For example, `3.14` and `2200.50` looks like they have different length, however, both are
     *       represented by 4 bytes, and a binary file help us with manipulating this information
     *       because he only needs the number of bytes to read or write, that is constant for each record.
     *
     *     • In this case, as we are using `int` and `float` as fields types, it is convenient to use
     *       a binary file to represent the values of this fields by the reason explained above.
     *
     *
     */
    class fixed_record {
        std::fstream file;          /// File instance that contains `p1::student` data
        std::string file_name;      /// The name of the file

    public:
        explicit fixed_record(std::string file_name);

        ~fixed_record();

        /// Initializes an empty file with a sentinel, this value indicates the first deleted record in the file.
        /// This member function should only be used once per file as it overwrites all the data.
        [[maybe_unused]] void init_file();

        /// Loads all the records in memory
        std::vector<std::pair<p2::student, int>> load();

        /// Writes a new record in a disk `file`
        void add(p2::student &record);

        /// Load the `pos` record in memory and return it
        p2::student read_record(int pos);

        /// Delete logically a record (without removing it from the file)
        void delete_record(int pos);
    };

    // test function, internally, instantiates a `p2::fixed_record` and use it to manipulate a disk file
    void test(const std::string &file_name);
}

/// Definitions of functions related to `p2::student` struct manipulation
namespace p2 {
    void init(p2::student &student) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "======= Student Information =======" << std::endl;

        std::cout << "Code: ";
        read_from_console(student.code, code_length);

        std::cout << "Name: ";
        read_from_console(student.name, name_length);

        std::cout << "Last name: ";
        read_from_console(student.last_name, last_name_length);

        std::cout << "Career: ";
        read_from_console(student.career, career_length);

        std::cout << "Cycle: ";
        std::cin >> student.cycle;

        std::cout << "Monthly Payment: ";
        std::cin >> student.monthly_payment;
    }

    void write(std::ostream &stream, p2::student &record, int &next_del) {
        stream.write(record.code, code_length);
        stream.write(record.name, name_length);
        stream.write(record.last_name, last_name_length);
        stream.write(record.career, career_length);
        stream.write((text) &record.cycle, int_sz);
        stream.write((text) &record.monthly_payment, float_sz);
        stream.write((text) &next_del, int_sz);
        stream << std::flush;
    }

    void read(std::istream &stream, p2::student &record, int &next_del) {
        stream.read(record.code, code_length);
        record.code[code_length - 1] = '\0';

        stream.read(record.name, name_length);
        record.name[name_length - 1] = '\0';

        stream.read(record.last_name, last_name_length);
        record.last_name[last_name_length - 1] = '\0';

        stream.read(record.career, career_length);
        record.career[career_length - 1] = '\0';

        stream.read((text) &record.cycle, int_sz);
        stream.read((text) &record.monthly_payment, float_sz);
        stream.read((text) &next_del, int_sz);
    }

    std::string to_string(p2::student &student) {
        std::stringstream ss;
        ss << "("
           << student.code << ", "
           << student.name << ", "
           << student.last_name << ", "
           << student.career << ", "
           << student.cycle << ", "
           << student.monthly_payment
           << ")";
        return ss.str();
    }
}

/// Definition of public member functions of `p2::fixed_record`
namespace p2 {
    fixed_record::fixed_record(std::string file_name) : file_name(std::move(file_name)) {
    }

    fixed_record::~fixed_record() = default;

    void fixed_record::init_file() {
        file.open(file_name, std::ios::out | std::ios::binary);
        int sentinel = -1;
        file.write((text) &sentinel, int_sz);
        file.close();
    }

    std::vector<std::pair<p2::student, int>> fixed_record::load() {
        file.open(file_name, std::ios::in | std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error(file_not_open);
        }

        std::vector<std::pair<p2::student, int>> records;
        // Reads the header in order to skip the firsts 4 bytes
        int next_del;
        file.read((text) &next_del, int_sz);

        // `i` Indicates the logic position of a record
        int i = 0;

        // Reads the information until the end of file is reached
        while (!file.eof()) {
            p2::student record{};

            // Reads the record information
            p2::read(file, record, next_del);

            // If the read fails, then the loop breaks
            if (file.fail()) {
                break;
            }

            // If `nex_del` is not equal to `0`, it means that this record is logically deleted
            if (next_del != 0) {
                ++i;
                continue;
            }
            records.emplace_back(record, i);
            ++i;
        }

        file.close();
        return records;
    }

    void fixed_record::add(p2::student &record) {
        file.open(file_name, std::ios::in | std::ios::out | std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error(file_not_open);
        }

        // Reads the first deleted record position
        int first_del;
        file.seekg(0);
        file.read((text) &first_del, int_sz);

        // Indicates the next deleted record of `record`
        int next_del = 0;

        // If the first deleted equals `-1`, it means that there is no deleted record in the disk-file.
        // In that case, the record is appended at the end of the file.
        if (first_del == -1) {
            file.seekp(0, std::ios::end);
            p2::write(file, record, next_del);
            file.close();
            return;
        }

        // Reads the second deleted record and stores it in `nex_del`
        file.seekg(first_del + record_size);
        file.read((text) &next_del, int_sz);

        // Seeks the first deleted record in order to overwrite his value with the new record
        file.seekp(first_del);
        first_del = 0;
        p2::write(file, record, first_del);

        // Updates the new first deleted record at the header
        file.seekp(0);
        file.write((text) &next_del, int_sz);

        file.close();
    }

    p2::student fixed_record::read_record(int pos) {
        // Verifies `pos`
        if (pos < 0) {
            throw std::invalid_argument(not_valid_position);
        }

        file.open(file_name, std::ios::in);
        if (!file.is_open()) {
            throw std::runtime_error(file_not_open);
        }

        // Seeks the record position
        file.seekg(int_sz + pos * (record_size + int_sz));
        p2::student record{};
        int next_del;

        // Reads the record information
        p2::read(file, record, next_del);

        if (file.fail()) {
            file.close();
            throw std::invalid_argument(not_valid_position);
        }

        if (next_del != 0) {
            file.close();
            throw std::invalid_argument(reading_deleted_record);
        }

        file.close();
        return record;
    }

    void fixed_record::delete_record(int pos) {
        if (pos < 0) {
            throw std::invalid_argument(not_valid_position);
        }

        file.open(file_name, std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error(file_not_open);
        }

        /// Reads the first deleted record position
        int first_del;
        file.seekg(0);
        file.read((text) &first_del, int_sz);

        /// Calculates the position of the record to be deleted
        int new_first_del = (int_sz + pos * (record_size + int_sz));

        /// Seeks the value of the next deleted record of the record at `pos`
        /// in order to verify if it is not already deleted
        int next_del;
        file.seekg(new_first_del + record_size);
        file.read((text) &next_del, int_sz);

        if (file.fail()) {
            file.close();
            throw std::invalid_argument(not_valid_position);
        }

        /// Before overwrite the disk pointers, verifies if the record to delete is already deleted
        if (next_del != 0) {
            file.close();
            throw std::invalid_argument(record_already_deleted);
        }

        /// If not, then overwrites the disk pointers
        file.seekp(new_first_del + record_size);
        file.write((text) &first_del, int_sz);

        /// Updates the new first deleted record
        file.seekp(0);
        file.write((text) &new_first_del, int_sz);

        file.close();
    }
}

/// Definition of test function
namespace p2 {
    void test(const std::string &file_name) {
        p2::fixed_record fr(file_name);
        std::system(clear_console);

        do {
            std::cout << menu_2 << std::endl;
            int option;
            do {
                std::cout << "Select an option: ";
                std::cin >> option;
            } while (option < 0 || option > 5);
            std::cout << std::endl;

            switch (option) {
                case 0: {
                    p2::student student{};
                    p2::init(student);
                    try {
                        fr.add(student);
                    } CATCH
                    std::cout << "The new record has been successfully written in disk" << std::endl;
                    break;
                }
                case 1 : {
                    try {
                        std::vector<std::pair<p2::student, int>> records = fr.load();
                        for (auto &[student, i]: records) {
                            std::cout << "[" << i << "] => " << to_string(student) << std::endl;
                        }
                    } CATCH
                    break;
                }
                case 2 : {
                    int position;
                    std::cout << "Enter the record position: ";
                    std::cin >> position;
                    try {
                        p2::student student = fr.read_record(position);
                        std::cout << "The [" << position << "] student is: " << to_string(student) << std::endl;
                    } CATCH
                    break;
                }
                case 3 : {
                    int position;
                    std::cout << "Enter the record position: ";
                    std::cin >> position;

                    char confirmation = ' ';
                    std::cout << std::endl << "This option will delete the record [" << position << "]" << std::endl;
                    std::cout << "Are you sure you want to continue? (y/n): ";
                    std::cin >> confirmation;

                    if (confirmation == 'y') {
                        try {
                            fr.delete_record(position);
                            std::cout << "The [" << position << "] student was deleted successfully" << std::endl;
                        } CATCH
                    }
                    break;
                }
                case 4 : {
                    char confirmation = ' ';
                    std::cout << "This option will clear all data at " << file_name << std::endl;
                    std::cout << "Are you sure you want to continue? (y/n): ";
                    std::cin >> confirmation;

                    if (confirmation == 'y') {
                        try {
                            fr.init_file();
                        } CATCH
                        std::cout << "The 'free list' file was initialized successfully" << std::endl;
                    }
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

#endif //FILE_SYSTEM_Q2_HPP
