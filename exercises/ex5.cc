// Copyright 2023 Adam Klein
// Name: Adam Klein
// UWemail: aklein47@uw.edu

#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc != 1) {  // checks for if exactly 1 paramiter was passed in
        std::cerr << "ERROR: incorect number of inputs\n";
        return EXIT_FAILURE;
    }
    int num;
    std::cout << "Which positive integer would you like me to factorize? ";
    std::cin >> num;
    if (num <= 0) {  // sees if num is a natual number
        std::cerr << "ERROR: input not a natual number\n";
        return EXIT_FAILURE;
    }
    for (int i = 1; i < num; i++) {
        if (num % i == 0) {
            std::cout << i << " ";
        }
    }
    std::cout << num << "\n";
    return EXIT_SUCCESS;
}
