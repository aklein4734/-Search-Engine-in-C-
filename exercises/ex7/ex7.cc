// Copyright 2023 Adam Klein
// Name: Adam Klein
// UWemail: aklein47@uw.edu

#include <iostream>
#include <cstdlib>


#include "Vector.h"

// tests to see if two vectors are equal
static bool Equals(vector333::Vector v1, vector333::Vector v2);

// tests to see if the getter functions work
static bool Test_Gets(vector333::Vector v, float x, float y, float z);

// tests to see if += overide works
static bool Test_add_equals(vector333::Vector v1,
                            vector333::Vector v2,
                            vector333::Vector v3);

// tests to see if -= overide works
static bool Test_sub_equals(vector333::Vector v1,
                            vector333::Vector v2,
                            vector333::Vector v3);

// tests to see if = overide works
static bool Test_equals(vector333::Vector v1, vector333::Vector v2);

// tests to see if vector * vector works
static bool Test_mult(vector333::Vector v1, vector333::Vector v2);

// tests to see if vector * k and k * vector works
static bool Test_mult_const(vector333::Vector v1,
                            vector333::Vector v2, float k);

// tests to see if + overide works
static bool Test_add(vector333::Vector v1,
                     vector333::Vector v2,
                     vector333::Vector v3);

// tests to see if - overide works
static bool Test_sub(vector333::Vector v1,
                     vector333::Vector v2,
                     vector333::Vector v3);

// test to see if prints work
static bool Test_print(vector333::Vector v, float x, float y, float z);

#define origin 0.0
#define margin 0.00001
#define x1 1.0
#define y1 2.0
#define z1 3.0
#define answer 14.0

int main(int argc, char* argv[]) {
  if (argc != 1) {
    std::cerr << "ERROR: Passed in paramiters" << std::endl;
    return EXIT_FAILURE;
  }
  vector333::Vector v0 = vector333::Vector();
  vector333::Vector v1 = vector333::Vector(x1, y1, z1);
  vector333::Vector v2 = vector333::Vector(v1);
  vector333::Vector v3 = vector333::Vector(x1 * y1, y1 * y1, z1 * y1);
  if (!Test_Gets(v1, x1, y1, z1) ||
      !Test_Gets(v0, origin, origin, origin) ||
      !Test_Gets(v2, x1, y1, z1)) {
    return EXIT_FAILURE;
  }

  if (!Test_sub_equals(v1, v2, v0) || !Test_add_equals(v0, v2, v2) ||
      !Test_equals(v2, v1) || !Test_mult(v1, v2) ||
      !Test_mult_const(v1, v3, y1) || !Test_add(v1, v2, v3) ||
      !Test_sub(v3, v2, v1) || !Test_print(v1, x1, y1, z1)) {
    return EXIT_FAILURE;
  }
  std::cout << "All tests Passed" << std::endl;
  return EXIT_SUCCESS;
}

static bool Equals(vector333::Vector v1, vector333::Vector v2) {
  if (!((v1.get_x() - v2.get_x() > -margin &&
         v1.get_x() - v2.get_x() < margin) &&
        (v1.get_y() - v2.get_y() > -margin &&
         v1.get_y() - v2.get_y() < margin) &&
        (v1.get_z() - v2.get_z() > -margin &&
         v1.get_z() - v2.get_z() < margin))) {
    std::cerr << "Expected: " << v1.get_x() << ", "
                              << v1.get_y() << ", "
                              << v1.get_z() << std::endl;
    std::cerr << "     Got: " << v2.get_x() << ", "
                              << v2.get_y() << ", "
                              << v2.get_z() << std::endl;
    return false;
  }
  return true;
}

static bool Test_Gets(vector333::Vector v, float x, float y, float z) {
  if (!((((v.get_x() - x) > -margin) && ((v.get_x() - x) < margin)) &&
      (((v.get_y() - y) > -margin) && ((v.get_y() - y) < margin)) &&
      (((v.get_z() - z) > -margin) && ((v.get_z() - z) < margin)))) {
    std::cerr << "ERROR: get functions failed" << std::endl;
    std::cerr << "Expected: " << x << ", " << y << ", " << z << std::endl;
    std::cerr << "     Got: " << v.get_x() << ", "
                              << v.get_y() << ", "
                              << v.get_z() << std::endl;
    return false;
  }
  return true;
}

static bool Test_add_equals(vector333::Vector v1,
                            vector333::Vector v2,
                            vector333::Vector v3) {
  v1 += v2;
  if (!Equals(v1, v3)) {
    std::cerr << "ERROR: '+=' override Failed" << std::endl;
    return false;
  }
  return true;
}

static bool Test_sub_equals(vector333::Vector v1,
                            vector333::Vector v2,
                            vector333::Vector v3) {
  v1 -= v2;
  if (!Equals(v1, v3)) {
    std::cerr << "ERROR: '-=' override Failed" << std::endl;
    return false;
  }
  return true;
}

static bool Test_equals(vector333::Vector v1, vector333::Vector v2) {
  v1 = v2;
  if (!Equals(v1, v2)) {
    std::cerr << "ERROR: '=' override Failed" << std::endl;
    return false;
  }
  return true;
}


static bool Test_mult(vector333::Vector v1, vector333::Vector v2) {
  if (v1 * v2 != answer) {
    std::cerr << "ERROR: '*' override Failed" << std::endl;
    return false;
  }
  return true;
}

static bool Test_mult_const(vector333::Vector v1,
                            vector333::Vector v2, float k) {
  if (!Equals(v1 * k, v2) || !Equals(v2, v1 * k)) {
    std::cerr << "ERROR: '*' override Failed" << std::endl;
    return false;
  }
  return true;
}

static bool Test_add(vector333::Vector v1,
                     vector333::Vector v2,
                     vector333::Vector v3) {
  if (!Equals(v1 + v2, v3)) {
    std::cerr << "ERROR: '+' override Failed" << std::endl;
    return false;
  }
  return true;
}

static bool Test_sub(vector333::Vector v1,
                     vector333::Vector v2,
                     vector333::Vector v3) {
  if (!Equals(v1 - v2, v3)) {
    std::cerr << "ERROR: '+' override Failed" << std::endl;
    return false;
  }
  return true;
}

static bool Test_print(vector333::Vector v, float x, float y, float z) {
  std::cout << v << std::endl;
  std::cout << "(" << v.get_x() <<
              ", " << v.get_y() <<
              ", " << v.get_z() << ")" << std::endl;
  return true;
}
