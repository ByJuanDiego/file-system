//
// Created by juandiego on 3/31/23.
//

#ifndef FILE_SYSTEM_P1_HPP
#define FILE_SYSTEM_P1_HPP

#include <iostream>
#include "fixedrecord.hpp"

void test1() {
    fixed_record fr("./data/datos1.txt");
    bool quit = false;

    do {
        int option;

        std::cout << std::endl;
        std::cout << "============== Menu ==============" << std::endl;
        std::cout << "Options " << std::endl;
        std::cout << "    [0]: Add a new record" << std::endl;
        std::cout << "    [1]: Read all records" << std::endl;
        std::cout << "    [2]: Read the ith record" << std::endl;
        std::cout << std::endl;

        do {
            std::cout << "Select an option: ";
            std::cin >> option;
        } while (option < 0 || option > 2);
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
            }
        }

        std::cout << std::endl;
        std::cout << "Exit? [0, 1]: ";
        std::cin >> quit;

    } while (!quit);
}

#endif // FILE_SYSTEM_P1_HPP