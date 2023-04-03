

#ifndef FILE_SYSTEM_FIXEDRECORD_HPP
#define FILE_SYSTEM_FIXEDRECORD_HPP

#include <fstream>
#include <utility>
#include <vector>
#include "student1.hpp"

namespace p1 {
    class fixed_record {

        std::fstream file;
        std::string file_name;
        p1::student *eliminated = nullptr;

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
        
        void eliminate(int pos);
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
                if(record->eliminado
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
    void fixed_record::eliminate(int pos){
        long max_pos = number_of_records() - 1;
        p1::student *tmp;
        p1::student *student{};
        if(pos < 0 || pos > max_pos){
            throw std::invalid_argument("Invalid position");
        }
        file.seekg(p1::record_size * pos);
        file >> student;
        student->borrado = true;
        tmp = this->eliminated;
        if(tmp == nullptr){
            this->eliminated = student; 
        }
        else{
            student->next = this->eliminated;
            this->eliminated = student;
        }
        

    }
}

#endif //FILE_SYSTEM_FIXEDRECORD_HPP
