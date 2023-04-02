//
// Created by juandiego on 3/31/23.
//

#ifndef FILE_SYSTEM_P1_HPP
#define FILE_SYSTEM_P1_HPP

#include <limits>
#include <iostream>
#include "fixedrecord.hpp"

void test1() {
    p1::fixed_record fr("./data/datos1.txt");

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
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cin.get();
        std::system("clear");

    } while (true);
}

#endif // FILE_SYSTEM_P1_HPP