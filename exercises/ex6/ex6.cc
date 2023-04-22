// Copyright 2023 Adam Klein
// Name: Adam Klein
// UWemail: aklein47@uw.edu

#include <iostream>
#include <cstdlib>

#include "Vector.h"

int main(int argc, char* argv[]) {
  Vector v = Vector(1.0, 2.0, 3.0);
  if (!Test_Gets(v, 1.0, 2.0, 3.0)) {

  }
  if (!Test_Constuct(v)) {

  }
}

static bool Test_Constuct(Vector v) {
  if (&v == NULL) {
    return false;
  }
  Vector orgin = Vector();
  return true;
}

static bool Test_Gets(Vector v, float x, float y, float z) {
  if (v.get_x() != x || v.get_y() != y || v.get_z() != z) {
    return false;
  }
  return true;
}