#include "../inc/tests/q1.hpp"
#include "../inc/tests/q2.hpp"
#include "../inc/tests/q3.hpp"
#include "../inc/tests/q4.hpp"

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
            p1::test("./assets/data/datos1.txt");
            break;
        case question::q2:
            p2::test("./assets/data/datos2.dat");
            break;
        case question::q3:
            p3::test("./assets/data/datos3.txt");
            break;
        case question::q4:
            p4::test("./assets/data/datos4.dat", "./assets/metadata/cabecera4.dat");
            break;
    }

    return EXIT_SUCCESS;
}
