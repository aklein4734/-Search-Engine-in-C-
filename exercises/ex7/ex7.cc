// Copyright 2023 Adam Klein
// Name: Adam Klein
// UWemail: aklein47@uw.edu

#include <iostream>
#include <cstdlib>

#include "Vector.h"
static bool Equals(Vector v1, Vector v2);
static bool Test_Gets(Vector v, float x, float y, float z);
static bool Test_add_equals(Vector v1, Vector v2, Vector v3);
static bool Test_sub_equals(Vector v1, Vector v2, Vector v3);
static bool Test_equals(Vector v1, Vector v2);
static bool Test_mult(Vector v1, Vector v2);
static bool Test_mult_const(Vector v1, Vector v2, float k);
static void Increment(Vector v);
static bool VerifyAdress(Vector v1, Vector *v2);

#define origin 0.0
#define margin 0.00001
#define x1 1.0
#define y1 2.0
#define z1 3.0
#define answer 14.0

int main(int argc, char* argv[]) {
  if (argc != 1) {
    std::cerr << "ERROR: Passed in paramiters\n";
    return EXIT_FAILURE;
  }
  Vector v0 = Vector();
  Vector v1 = Vector(x1, y1, z1);
  Vector v2 = Vector(v1);
  if (!Test_Gets(v1, x1, y1, z1) ||
      !Test_Gets(v0, origin, origin, origin) ||
      !Test_Gets(v2, x1, y1, z1)) {
    return EXIT_FAILURE;
  }

  if (!Test_sub_equals(v1, v2, v0) || !Test_add_equals(v0, v2, v2) ||
      !Test_equals(v2, v1) || !Test_mult(v1, v2)) {
    return EXIT_FAILURE;
  }
  Increment(v1);
  if (Equals(v1, v2)) {
    std::cout << "Vector: pass-by-value\n";
  } else {
    std::cout << "Vector: pass-by-reference\n";
  }
  if (VerifyAdress(v0, &v0)) {
    std::cout << "Ref: same address\n";
  } else {
    std::cout << "Ref: different address\n";
  }
  return EXIT_SUCCESS;
}

static bool Equals(Vector v1, Vector v2) {
  if (!((v1.get_x() - v2.get_x() > -margin &&
         v1.get_x() - v2.get_x() < margin) &&
        (v1.get_y() - v2.get_y() > -margin &&
         v1.get_y() - v2.get_y() < margin) &&
        (v1.get_z() - v2.get_z() > -margin &&
         v1.get_z() - v2.get_z() < margin))) {
    std::cerr << "Expected: " << v1.get_x() << ", "
                              << v1.get_y() << ", "
                              << v1.get_z() << "\n";
    std::cerr << "     Got: " << v2.get_x() << ", "
                              << v2.get_y() << ", "
                              << v2.get_z() << "\n";
    return false;
  }
  return true;
}

static bool Test_Gets(Vector v, float x, float y, float z) {
  if (!((((v.get_x() - x) > -margin) && ((v.get_x() - x) < margin)) &&
      (((v.get_y() - y) > -margin) && ((v.get_y() - y) < margin)) &&
      (((v.get_z() - z) > -margin) && ((v.get_z() - z) < margin)))) {
    std::cerr << "ERROR: get functions failed\n";
    std::cerr << "Expected: " << x << ", " << y << ", " << z << "\n";
    std::cerr << "     Got: " << v.get_x() << ", "
                              << v.get_y() << ", "
                              << v.get_z() << "\n";
    return false;
  }
  return true;
}

static bool Test_add_equals(Vector v1, Vector v2, Vector v3) {
  v1 += v2;
  if (!Equals(v1, v3)) {
    std::cerr << "ERROR: '+=' override Failed\n";
    return false;
  }
  return true;
}

static bool Test_sub_equals(Vector v1, Vector v2, Vector v3) {
  v1 -= v2;
  if (!Equals(v1, v3)) {
    std::cerr << "ERROR: '-=' override Failed\n";
    return false;
  }
  return true;
}

static bool Test_equals(Vector v1, Vector v2) {
  v1 = v2;
  if (!Equals(v1, v2)) {
    std::cerr << "ERROR: '=' override Failed\n";
    return false;
  }
  return true;
}


static bool Test_mult(Vector v1, Vector v2) {
  if (v1 * v2 != answer) {
    std::cerr << "ERROR: '*' override Failed\n";
    return false;
  }
  return true;
}

static bool Test_mult_const(Vector v1, Vector v2, float k) {
  if (Equals(v1 * k, v2)) { // need to work on this
    std::cerr << "ERROR: '*' override Failed\n";
    return false;
  }
  return true; 
}

static void Increment(Vector v) {
  Vector v0 = Vector(1.0, 1.0, 1.0);
  v += v0;
}

static bool VerifyAdress(Vector v1, Vector *v2) {
  return &v1 == v2;
}
