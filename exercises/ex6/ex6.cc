// Copyright 2023 Adam Klein
// Name: Adam Klein
// UWemail: aklein47@uw.edu

#include <iostream>
#include <cstdlib>

#include "Vector.h"
#define x1 1.0
#define y1 2.0
#define z1 3.0

int main(int argc, char* argv[]) {
  Vector v = Vector(x1, y1, z1);
  if (!Test_Gets(v) || !Test_Constuct(v)) {
    return EXIT_FAILURE;
  }
}

static bool Test_Constuct(Vector v) {
  if (&v == NULL) {
    std::cerr << "ERROR: Your get functions are wrorg!";
    return false;
  }
  return true;
}

static bool Test_Gets(Vector v) {
  if (v.get_x() != x1 || v.get_y() != y1 || v.get_z() != z1) {
    std::cerr << "ERROR: get functions failed";
    return false;
  }
  return true;
}

static bool Test_Set() {
  return true;
}

static bool Test_add() {
  return true;
}

static bool Test_mult() {
  return true;
}