// Copyright 2023 Adam Klein
// Name: Adam Klein
// UWemail: aklein47@uw.edu

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

double sumPi(int32_t);

int main(int argc, char* argv[]) {
    if (argc != 2) {  // checks for if exactly 1 paramiter was passed in
        fprintf(stderr, "ERROR: incorect number of inputs\n");
        return EXIT_FAILURE;
    }
    char* end;
    int32_t runs = strtol(argv[1], &end, 10);
    if (end - argv[1] != strlen(argv[1])) {  // sees if argv[1] is an int
        fprintf(stderr, "ERROR: input not an integer\n");
        return EXIT_FAILURE;
    }
    if (runs < 0) {  // sees if runs is a positive int
        fprintf(stderr, "ERROR: input not a positive integer\n");
        return EXIT_FAILURE;
    }
    printf("Our estimate of Pi is %0.20f\n", sumPi(runs));
    return EXIT_SUCCESS;
}

double sumPi(int32_t runs) {
    double pi = 3.0;  // step 0 in the infinite series
    for (int i = 1; i <= runs; i++) {
        double iteration = 4.0 / (2 * i * (2 * i + 1) * (2 * i + 2));
        if (i % 2 == 1) {  // checks wheter it's an even or odd step
            pi = pi + iteration;
        } else {
            pi = pi - iteration;
        }
    }
    return pi;
}
