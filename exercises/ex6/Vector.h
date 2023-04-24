// Copyright 2023 Adam Klein
// Name: Adam Klein
// UWemail: aklein47@uw.edu

#ifndef VECTOR_H_
#define VECTOR_H_
class Vector {
 public:
  // Contructs a 3d zero Vector
  Vector();
  // Consructs a 3d vector with values x, y z
  Vector(const float x, const float y, const float z);
  // Copies the inputed vector
  Vector(const Vector &v);
  // Detructs the vector
  ~Vector() {}
  // gets _x from Vector
  float get_x() const {return _x;}
  // gets _y from Vector
  float get_y() const {return _y;}
  // gets _z from Vector
  float get_z() const {return _z;}

  // Override the "=", "+=", and "-=" operators.
  Vector& operator=(const Vector& v);
  Vector& operator+=(const Vector& v);
  Vector& operator-=(const Vector& v);



 private:
  float _x;
  float _y;
  float _z;
};  // class Vector

// Override the "*" operator.
float operator*(const Vector& v1, const Vector& v2);
#endif  // VECTOR_H_
