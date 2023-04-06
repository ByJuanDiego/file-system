#include <unordered_map>
#include <iostream>

#include "../inc/p1/p1.h"
#include "../inc/p2/p2.h"
#include "../inc/p3/p3.h"
#include "../inc/p4/p4.h"

int main(int argc, char *argv[]) {
    std::unordered_map<std::string, void (*)()> test = {{"1", test1},
                                                        {"2", test2},
                                                        {"3", test3},
                                                        {"4", test4}};

    test[std::string(((argc == 1) || (test.find(std::string(argv[1])) == test.end())) ? "2" : argv[1])]();

    return EXIT_SUCCESS;
}
