// Copyright 2023 Adam Klein
// Name: Adam Klein
// UWemail: aklein47@uw.edu

#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>

namespace vector333 {

class Vector {
 public:
  // Contructs a 3d zero Vector
  Vector();
  // Consructs a 3d vector with values x, y z
  Vector(const float x, const float y, const float z);
  // Copies the inputed vector
  Vector(const Vector &v);
  // Detructs the vector
  ~Vector();
  // gets _x from Vector
  float get_x() const {return vec[0];}
  // gets _y from Vector
  float get_y() const {return vec[1];}
  // gets _z from Vector
  float get_z() const {return vec[2];}

  // Override the "=", "+=", and "-=" operators.
  Vector& operator=(const Vector& v);
  Vector& operator+=(const Vector& v);
  Vector& operator-=(const Vector& v);



 private:
  float *vec;
};  // class Vector

// Override the "*" operator.
float operator*(const Vector& v1, const Vector& v2);

// Override the "*" operator.
Vector operator*(const Vector& v1, const float k);

// Override the "+" operator.
Vector operator+(const Vector& v1, const Vector& v2);

// Override the "-" operator.
Vector operator-(const Vector& v1, const Vector& v2);

// Override the outstream.
std::ostream& operator<<(std::ostream& in, Vector& a);
}  // namespace vector333
#endif  // VECTOR_H_
