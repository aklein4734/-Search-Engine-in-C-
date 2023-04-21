#ifndef VECTOR
#define VECTOR
class Vector {
  public:
  Vector();
  Vector(float xx, float yy, float zz);
  Vector(Vector &v);
  ~Vector();
  float get_x();
  float get_y();
  float get_z();
  void Vector_set(Vector v);
  void Vector_add(Vector v);
  float Vector_mult(Vector v);



  private:
  float x;
  float y;
  float z;
};
#endif
