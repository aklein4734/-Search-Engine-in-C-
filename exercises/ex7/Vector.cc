// Copyright 2023 Adam Klein
// Name: Adam Klein
// UWemail: aklein47@uw.edu

#include "Vector.h"

  Vector::Vector() {
    this->vec = new float[3];
    this->vec[0] = 0.0;
    this->vec[1] = 0.0;
    this->vec[2] = 0.0;
  }
  Vector::Vector(const float x, const float y, const float z) {
    this->vec = new float[3];
    this->vec[0] = x;
    this->vec[1] = y;
    this->vec[2] = z;
  }
  Vector::Vector(const Vector &v) {
    this->vec = new float[3];
    this->vec[0] = v.vec[0];
    this->vec[1] = v.vec[1];
    this->vec[2] = v.vec[2];
  }
  Vector::~Vector() {
    delete(vec);
  }
  Vector& Vector::operator=(const Vector& v) {
    if (this != &v) {
        this->vec[0] = v.vec[0];
        this->vec[1] = v.vec[1];
        this->vec[2] = v.vec[2];
    }
    return *this;
  }
  Vector& Vector::operator+=(const Vector& v) {
    this->vec[0] += v.vec[0];
    this->vec[1] += v.vec[1];
    this->vec[2] += v.vec[2];
    return *this;
  }
    Vector& Vector::operator-=(const Vector& v) {
    this->vec[0] -= v.vec[0];
    this->vec[1] -= v.vec[1];
    this->vec[2] -= v.vec[2];
    return *this;
  }
  float operator*(const Vector& v1, const Vector& v2) {
    float dot = v1.get_x() * v2.get_x();
    dot += v1.get_y() * v2.get_y();
    return dot + (v1.get_z() * v2.get_z());
  }
  Vector operator*(const Vector& v1, const float k) {
    return Vector(v1.get_x() * k, v1.get_y() * k, v1.get_z() * k);
  }
  Vector operator+(const Vector& v1, const Vector& v2) {
    return Vector(v1.get_x() + v2.get_x(), v1.get_y() + v2.get_y(), v1.get_z() + v2.get_z());
  }
  Vector operator-(const Vector& v1, const Vector& v2) {
    return Vector(v1.get_x() - v2.get_x(), v1.get_y() - v2.get_y(), v1.get_z() - v2.get_z());
  }
