

//#ifndef FILE_SYSTEM_FIXEDRECORD_HPP
//#define FILE_SYSTEM_FIXEDRECORD_HPP
//
//#include <fstream>
//#include <utility>
//#include <vector>
//#include "student2.hpp"
//
//namespace p2 {
//    class fixed_record {
//
//        std::fstream file;
//        std::string file_name;
//        p2::student eliminated;
//        bool head = false;
//        inline long number_of_records() {
//            file.seekg(0, std::ios::end);
//            long file_size = file.tellg();
//            file.seekg(0);
//            return (file_size) / (p2::record_size);
//        }
//
//    public:
//        explicit fixed_record(std::string file_name);
//
//        ~fixed_record();
//
//        std::vector<p2::student> load();
//
//        void add(p2::student &record);
//
//        p2::student read_record(int pos);
//
//        void eliminate(int pos);
//    };
//
//    fixed_record::fixed_record(std::string file_name) : file_name(std::move(file_name)) {
//    }
//
//    fixed_record::~fixed_record() = default;
//
//    std::vector<p2::student> fixed_record::load() {
//        file.open(file_name, std::ios::in);
//        std::vector<p2::student> records;
//        long n_records = number_of_records();
//
//        if (file.is_open()) {
//            for (int i = 0; i < n_records; ++i) {
//                p2::student record{};
//                file >> record;
//                if(record.eliminado)
//                records.push_back(record);
//            }
//        }
//
//        file.close();
//        return records;
//    }
//
//    void fixed_record::add(p2::student &record) {
//        file.open(file_name, std::ios::app);
//
//        if (!file.is_open()){
//            std::cerr << "Cannot open the file\n";
//            return;
//        }
//        if(this->head == true){
//            auto tmp = this->eliminated;
//            int pos = int(tmp.code);
//            file.seekg(p2::record_size * pos);
//            this->eliminated = this->eliminated.next;
//        }
//        file << record;
//        file.close();
//    }
//
//    p2::student fixed_record::read_record(int pos) {
//        file.open(file_name, std::ios::in);
//        p2::student student{};
//        long max_pos = number_of_records() - 1;
//        if (pos > max_pos || pos < 0) {
//            throw std::invalid_argument("invalid position");
//        }
//
//        file.seekg(p2::record_size * pos);
//        file >> student;
//        if(student.eliminado == 1){
//            throw std::invalid_argument("Posicion eliminada");
//        }
//        file.close();
//        return student;
//    }
//    void fixed_record::eliminate(int pos){
//        long max_pos = number_of_records() - 1;
//        p2::student tmp;
//        p2::student student{};
//        if(pos < 0 || pos > max_pos){
//            throw std::invalid_argument("Invalid position");
//        }
//        file.seekg(p2::record_size * pos);
//        file >> student;
//        student.eliminado = 1;
//        tmp = this->eliminated;
//        if(this->head == false){
//            this->eliminated = student;
//            head = true;
//        }
//        else{
//            student.next = this->eliminated;
//            this->eliminated = student;
//        }
//
//
//    }
//}
//
//#endif //FILE_SYSTEM_FIXEDRECORD_HPP
