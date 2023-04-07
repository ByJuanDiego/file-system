#ifndef FILE_SYSTEM_P2_HPP
#define FILE_SYSTEM_P2_HPP

#include <fstream>
#include <utility>
#include <vector>
#include <sstream>
#include <limits>
#include <cstring>

#include "func/read.hpp"
#include "global.hpp"

namespace p2 {

    constexpr int code_length = 5;
    constexpr int name_length = 11;
    constexpr int last_name_length = 20;
    constexpr int career_length = 15;

    struct student {
        char code[code_length];
        char name[name_length];
        char last_name[last_name_length];
        char career[career_length];

        int cycle;
        float monthly_payment;
    };

    const int record_size = sizeof(p2::student) - 1;

    void write(std::ostream &stream, p2::student &p, int &next_del) {
        stream.write(p.code, code_length);
        stream.write(p.name, name_length);
        stream.write(p.last_name, last_name_length);
        stream.write(p.career, career_length);
        stream.write((text) &p.cycle, int_sz);
        stream.write((text) &p.monthly_payment, float_sz);
        stream.write((text) &next_del, int_sz);
        stream << std::flush;
    }

    void read(std::istream &stream, p2::student &p, int &next_del) {
        stream.read(p.code, code_length);
        p.code[code_length - 1] = '\0';

        stream.read(p.name, name_length);
        p.name[name_length - 1] = '\0';

        stream.read(p.last_name, last_name_length);
        p.last_name[last_name_length - 1] = '\0';

        stream.read(p.career, career_length);
        p.career[career_length - 1] = '\0';

        stream.read((text) &p.cycle, int_sz);
        stream.read((text) &p.monthly_payment, float_sz);
        stream.read((text) &next_del, int_sz);
    }

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

    /** Class in charge of manipulate `p2::student` struct
     *
     * This class allows to write, read, load and delete `p2::student` records from a binary file.
     * Uses a implementation of `free-list` to delete a record logically.
     */
    class fixed_record {
        std::fstream file;
        std::string file_name;

    public:
        explicit fixed_record(std::string file_name);

        ~fixed_record();

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
    void test(const std::string &file_name) {

        p2::fixed_record fr(file_name);

        do {
            int option;

            std::cout << std::endl;
            std::cout << "============== Menu ==============" << std::endl;
            std::cout << "Options " << std::endl;
            std::cout << "    [0]: Add a new record" << std::endl;
            std::cout << "    [1]: Read all records" << std::endl;
            std::cout << "    [2]: Read the ith record" << std::endl;
            std::cout << "    [3]: Eliminate the ith record" << std::endl;
            std::cout << "    [4]: Exit" << std::endl;
            std::cout << std::endl;

            do {
                std::cout << "Select an option: ";
                std::cin >> option;
            } while (option < 0 || option > 4);
            std::cout << std::endl;

            switch (option) {
                case 0 : {
                    p2::student student{};
                    p2::init(student);
                    fr.add(student);
                    break;
                }
                case 1 : {
                    std::vector<std::pair<p2::student, int>> records = fr.load();
                    for (auto& [student, i]: records) {
                        std::cout << "[" << i << "] => " << to_string(student) << std::endl;
                    }
                    break;
                }
                case 2 : {
                    int position;
                    std::cout << "Enter the record position: ";
                    std::cin >> position;
                    p2::student student = fr.read_record(position);
                    std::cout << "The [" << position << "] student is: " << to_string(student) << std::endl;
                    break;
                }
                case 3 : {
                    int position;
                    std::cout << "Enter the record position: ";
                    std::cin >> position;
                    fr.delete_record(position);
                    std::cout << "The [" << position << "] student was deleted successfully" << std::endl;
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

namespace p2 {
    fixed_record::fixed_record(std::string file_name) : file_name(std::move(file_name)) {
    }

    fixed_record::~fixed_record() = default;

    std::vector<std::pair<p2::student, int>> fixed_record::load() {
        file.open(file_name, std::ios::in | std::ios::binary);
        std::vector<std::pair<p2::student, int>> records;

        if (!file.is_open()) {
            std::cerr << "Cannot open the file" << std::endl;
            return records;
        }

        int next_del;
        file.read((text) &next_del, int_sz);

        int i = 0;
        while (!file.eof()) {
            p2::student record{};
            p2::read(file, record, next_del);

            if (file.fail()) {
                break;
            }
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
            std::cerr << "Cannot open the file" << std::endl;
            return;
        }

        int first_del;
        file.seekg(0);
        file.read((text) &first_del, int_sz);

        int next_del = 0;
        if (first_del == -1) {
            file.seekp(0, std::ios::end);
            p2::write(file, record, next_del);
            file.close();
            return;
        }

        file.seekg(first_del + record_size);
        file.read((text) &next_del, int_sz);

        file.seekp(first_del);
        first_del = 0;
        p2::write(file, record, first_del);

        file.seekp(0);
        file.write((text) &next_del, int_sz);

        file.close();
    }

    p2::student fixed_record::read_record(int pos) {
        if (pos < 0) {
            throw std::invalid_argument("invalid position");
        }

        file.open(file_name, std::ios::in);

        file.seekg(int_sz + pos * (record_size + int_sz));
        p2::student record{};
        int next_del;

        p2::read(file, record, next_del);

        if (next_del != 0) {
            throw std::invalid_argument("a deleted record is @ this position");
        }

        file.close();
        return record;
    }

    void fixed_record::delete_record(int pos) {
        if (pos < 0) {
            throw std::invalid_argument("invalid position");
        }

        file.open(file_name, std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);

        int first_del;
        file.seekg(0);
        file.read((text) &first_del, int_sz);

        int new_first_del = (int_sz + pos * (record_size + int_sz));

        /// before overwrite the disk pointers, verifies if the record to delete is already deleted
        int next_del;
        file.seekg(new_first_del + record_size);
        file.read((text) &next_del, int_sz);
        if (next_del != 0) {
            throw std::invalid_argument("the record @ this position is already deleted");
        }

        /// if not, then overwrites the disk pointers
        file.seekp(new_first_del + record_size);
        file.write((text) &first_del, int_sz);

        file.seekp(0);
        file.write((text) &new_first_del, int_sz);

        file.close();
    }
}

#endif //FILE_SYSTEM_P2_HPP
