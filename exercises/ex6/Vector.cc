// Copyright 2023 Adam Klein
// Name: Adam Klein
// UWemail: aklein47@uw.edu

#include "Vector.h"

  Vector::Vector() {
    this->_x = 0.0;
    this->_y = 0.0;
    this->_y = 0.0;
  }
  Vector::Vector(const float x, const float y, const float z) {
    this->_x = x;
    this->_y = y;
    this->_z = z;
  }
  Vector::Vector(const Vector &v) {
    this->_x = v._x;
    this->_y = v._y;
    this->_z = v._z;
  }
  Vector& Vector::operator=(const Vector& v) {
    if (this != &v) {
      this->_x = v._x;
      this->_y = v._y;
      this->_z = v._z;
    }
    return *this;
  }
  Vector& Vector::operator+=(const Vector& v) {
    this->_x += v._x;
    this->_y += v._y;
    this->_z += v._z;
    return *this;
  }
    Vector& Vector::operator-=(const Vector& v) {
    this->_x -= v._x;
    this->_y -= v._y;
    this->_z -= v._z;
    return *this;
  }
  float operator*(const Vector& v1, const Vector& v2) {
    float dot = v1.get_x() * v2.get_x();
    dot += v1.get_y() * v2.get_y();
    return dot + (v1.get_z() * v2.get_z());
  }
