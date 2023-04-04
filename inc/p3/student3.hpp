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
}

#endif //FILE_SYSTEM_STUDENT3_HPP
