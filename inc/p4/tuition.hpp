//
// Created by juandiego on 4/4/23.
//

#ifndef FILE_SYSTEM_TUITION_HPP
#define FILE_SYSTEM_TUITION_HPP

#include <string>
#include <limits>
#include <fstream>
#include <iostream>

typedef char *text;
const int int_sz = sizeof(int);
const int float_sz = sizeof(float);

namespace p4 {

    struct tuition {
        std::string code;
        int cycle;
        float monthly_payment;
        std::string observations;
    };

    void init(p4::tuition &tuition) {
        std::cout << "======= Tuition Information =======" << std::endl;

        std::cout << "Code: ";
        std::cin >> tuition.code;

        std::cout << "Current cycle: ";
        std::cin >> tuition.cycle;

        std::cout << "Monthly payment: ";
        std::cin >> tuition.monthly_payment;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Observations: ";
        std::getline(std::cin, tuition.observations);
    }

    void read(p4::tuition &record, std::fstream &stream) {
        int n_code_bytes, n_observations_bytes;

        /// Reading the code length
        stream.read((text) &n_code_bytes, int_sz);

        char *code = new char[n_code_bytes + 1];
        /// Reading the code
        stream.read(code, n_code_bytes);
        code[n_code_bytes] = '\0';
        record.code = code;
        delete[] code;

        /// Reading the cycle
        stream.read((text) &record.cycle, int_sz);

        /// Reading the monthly payment
        stream.read((text) &record.monthly_payment, int_sz);

        /// Reading the observations length
        stream.read((text) &n_observations_bytes, int_sz);

        char *observations = new char[n_observations_bytes + 1];
        /// Reading the observations
        stream.read(observations, n_observations_bytes);
        observations[n_observations_bytes] = '\0';
        record.observations = observations;
        delete[] observations;
    }

    std::string to_string(p4::tuition &record) {
        std::stringstream ss;
        std::cout << record.code << std::endl;
        ss << "("
           << record.code << ", "
           << record.cycle << ", "
           << record.monthly_payment << ", "
           << record.observations
           << ")";
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &stream, p4::tuition &record) {
        int code_length = (int) record.code.length();
        int observations_length = (int) record.observations.length();

        /// Writing the code length (variable length)
        stream.write((text) &code_length, int_sz);
        stream.write((text) record.code.c_str(), code_length);

        /// Writing the current cycle
        stream.write((text) &record.cycle, int_sz);

        /// Writing the monthly payment
        stream.write((text) &record.monthly_payment, float_sz);

        /// Writing the observations (variable length)
        stream.write((text) &observations_length, int_sz);
        stream.write((text) record.observations.c_str(), observations_length);

        return stream;
    }

}

#endif //FILE_SYSTEM_TUITION_HPP
