// Copyright 2023 Adam Klein
// UWemail: aklein47@uw.edu
// Name: Adam Klein

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void DumpBytes(void* pointer, int32_t size);
void CopyAndSort(uint8_t orignal[], uint8_t new[], int size);

int main(int argc, char* argv[]) {
    int32_t int_val = 1;
    float   float_val = 1.0f;
    uint8_t arr_unsorted[] = {3, 2, 0, 8, 17, 6, 10, 7, 8, 1, 12};
    uint8_t arr_sorted[]   = {0, 0, 0, 0,  0, 0,  0, 0, 0, 0,  0};

    DumpBytes(&int_val, sizeof(int_val));
    DumpBytes(&float_val, sizeof(float_val));
    DumpBytes(arr_unsorted, sizeof(arr_unsorted));
    CopyAndSort(arr_unsorted, arr_sorted, sizeof(arr_unsorted) /
        sizeof(uint8_t));
    DumpBytes(arr_sorted, sizeof(arr_sorted));

    return EXIT_SUCCESS;
}

// Dumps the number of bytes (size) at the indicated pointer 
void DumpBytes(void* pointer, int32_t size) {
    if (size < 0) {  // sees if size is a positive int
        fprintf(stderr, "ERROR: negitive number of bytes\n");
        return;
    }
    printf("The %d bytes starting at %p are:", size, pointer);
    uint8_t* a_byte = pointer;
    for (int i = 0; i < size; i++) {
        printf(" %02x", *a_byte);
        a_byte = a_byte + 1;
    }
    printf("\n");
}

// Copys the values from the orignal array into the new array
// the method must be provided with the size of the arrays to copy them
// Then the method sorts the new array into accending order
void CopyAndSort(uint8_t orignal[], uint8_t new[], int size) {
    if (size < 0) {  // sees if size is a positive int
        fprintf(stderr, "ERROR: negitive size of the array\n");
        return;
    }
    DumpBytes(orignal, size);
    for (int i = 0; i < size; i++) {  // moves the data from orignal to new
        new[i] = orignal[i];
    }
    int8_t sorted = 0;  // indicator varible to see if the array is sorted
    while (sorted == 0) {
        sorted = 1;
        for (int i = 0; i < (size - 1); i++) {
            if (new[i] > new[i + 1]) {  // checks for wrong ordering if so swap
                sorted = 0;
                int temp = new[i];
                new[i] = new[i + 1];
                new[i + 1] = temp;
            }
        }
    }
}
