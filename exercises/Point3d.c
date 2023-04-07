

#include "Point3d.h"

Point3d* Point3d_Allocate(int32_t x, int32_t y, int32_t z) {
    Point3d *point = (Point3d *) malloc(sizeof(Point3d));
    if (point == NULL){
        exit(EXIT_FAILURE);
    }
    point->x = x;
    point->y = y;
    point->z = z;
    return point;
}

void Point3d_Scale(Point3d* point, int32_t value){
    point->x = point->x * value;
    point->y = point->y * value;
    point->z = point->z * value;
}

Point3d Point3d_GetOrigin() {
    Point3d point = {0, 0, 0};
    return point;
}
