#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifndef POINT3D_H_
#define POINT3D_H_
typedef struct point_st {
    int32_t x;
    int32_t y;
    int32_t z;
} Point3d;

Point3d* Point3d_Allocate(int32_t x, int32_t y, int32_t z);

void Point3d_Scale(Point3d* point, int32_t value);

Point3d Point3d_GetOrigin();
#endif