#include "Vector.h"

  Vector::Vector() {
    this->x = 0.0;
    this->y = 0.0;
    this->y = 0.0;
  }
  Vector::Vector(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }
  Vector::Vector(Vector &v){
    this->x = v.get_x();
    this->y = v.get_y();
    this->z = v.get_z();
  }
  Vector::~Vector() {

  }
  float Vector::get_x() {
    return this->x;
  }
  float Vector::get_y() {
    return this->y;
  }
  float Vector::get_z() {
    return this->z;
  }
  void Vector::Vector_set(Vector v) {
    this->x = v.get_x();
    this->y = v.get_y();
    this->z = v.get_z();
  }
  void Vector::Vector_add(Vector v) {
    this->x += v.get_x();
    this->y += v.get_y();
    this->z += v.get_z();
  }
  float Vector::Vector_mult(Vector v) {
    float dot = this->x * v.get_x();
    dot += this->y * v.get_y();
    return dot + (this->z * v.get_z());
  }
