// Copyright 2023 Adam Klein
// UWemail: aklein47@uw.edu
// Name: Adam Klein

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "Point3d.h"

int main(int argc, char* argv[]) {
    Point3d* point = Point3d_Allocate(1, 1, 1);
    if (point == NULL) {
        return EXIT_FAILURE;
    }
    Point3d_Scale(point, 2);
    Point3d origin = Point3d_GetOrigin();
    Point3d_Scale(&origin, 2);
    free(point);
}
