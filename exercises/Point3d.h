// Copyright 2023 Adam Klein
// UWemail: aklein47@uw.edu
// Name: Adam Klein

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifndef POINT3D_H_
#define POINT3D_H_
// creates the Point3D typedef
typedef struct point_st {
    int32_t x;
    int32_t y;
    int32_t z;
} Point3d;

// allocates memory for a Point3d
// and initializes the point with the passed in paramaters
// returns a pointer to the allocated point
Point3d* Point3d_Allocate(int32_t x, int32_t y, int32_t z);

// scales the point by the inputed value
void Point3d_Scale(Point3d* point, int32_t value);

// returns a Point3d that is the origin
Point3d Point3d_GetOrigin();
#endif  // POINT3D_H_
