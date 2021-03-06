// position_vector.h
// Vector object for velocity, position, force etc. of the body object

#ifndef __POSVECTOR_H_INCLUDED__
#define __POSVECTOR_H_INCLUDED__

#include "matrix.h"
#include <vector>

using namespace std;

class Vector {
	double x;
	double y;
	double z;

  public:
  	// Constructors
  	Vector();
  	Vector(double _x, double _y, double _z);

  	// Set Methods
	void Set(double _x, double _y, double _z) { x = _x; y = _y; z = _z; };
	void SetX(double _x) { x = _x; };
	void SetY(double _y) { y = _y; };
	void SetZ(double _z) { z = _z; };

	// Get Methods
	double GetX() { return x; };
	double GetY() { return y; };
	double GetZ() { return z; };

	// Calculation Methods
	Vector Add(Vector other);
	Vector Subtract(Vector other);
	Vector Multiply(double scalar);
	Vector Divide(double scalar);
	double DotProduct(Vector other);
	double Magnitude();

	// Transformation Methods
	Vector Transform(Matrix transformationMatrix);
	Vector RotateY(double angle);
	Vector RoundValues();
};

#endif