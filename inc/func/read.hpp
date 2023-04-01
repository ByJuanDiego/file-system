//
// Created by juandiego on 3/31/23.
//

#ifndef FILE_SYSTEM_READ_HPP
#define FILE_SYSTEM_READ_HPP

#include <iostream>
#include <string>

void read_from_console(char buffer[], int size) {
    std::string temp;
    std::getline(std::cin >> std::ws, temp, '\n');
    std::cin.clear();

    for (int i = 0; i < size; i++) {
        buffer[i] = (i < temp.size()) ? temp[i] : ' ';
    }

    buffer[size - 1] = '\0';
}

#endif //FILE_SYSTEM_READ_HPP
