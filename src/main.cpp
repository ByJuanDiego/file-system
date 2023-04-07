#include "../inc/p1.hpp"
#include "../inc/p2.hpp"
#include "../inc/p3.hpp"
#include "../inc/p4.hpp"

enum class question {
    q1 = 1, q2, q3, q4
};

int main(int argc, char *argv[]) {
    int n_test{};
    question q;

    if (argc == 1) {
        do {
            std::cout << "Enter the test number: ";
            std::cin >> n_test;
        } while (n_test < 1 || n_test > 4);
        q = (question) n_test;
    } else {
        q = (question) std::stoi(argv[1]);
    }

    switch (q) {
        case question::q1:
            p1::test("./data/datos1.txt");
            break;
        case question::q2:
            p2::test("./data/datos2.dat");
            break;
        case question::q3:
            p3::test("./data/datos3.txt");
            break;
        case question::q4:
            p4::test("./data/datos4.dat", "./metadata/cabecera4.dat");
            break;
    }

    return EXIT_SUCCESS;
}
