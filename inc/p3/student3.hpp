//
// Created by juandiego on 4/1/23.
//

#ifndef FILE_SYSTEM_STUDENT3_HPP
#define FILE_SYSTEM_STUDENT3_HPP

#include <string>
#include <iostream>

namespace p3 {

    struct student {
        std::string name;
        std::string last_name;
        std::string career;
        float monthly_payment;
    };

    void init(p3::student &student) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

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

    void read(p3::student &p, char * line) {
        char* cursor = line;

        cursor = strtok(cursor, "|");
        p.name = std::string(cursor);

        cursor = strtok(nullptr, "|");
        p.last_name = std::string(cursor);

        cursor = strtok(nullptr, "|");
        p.career = std::string(cursor);

        cursor = strtok(nullptr, "\n");
        p.monthly_payment = std::stof(std::string(cursor));
    }

    std::string to_string(p3::student &student) {
        std::stringstream ss;
        ss << "(" << student.name << ", " << student.last_name << ", " << student.career << ", "
           << student.monthly_payment << ")";
        return ss.str();
    }
}

#endif //FILE_SYSTEM_STUDENT3_HPP
