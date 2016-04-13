#pragma once
#include <iostream>
#include <cmath>
#include "Vector3d.h"

using namespace std;

class MatrizR{
public:
	float mat[3][3];
	MatrizR();
	MatrizR(Vector3d v1, Vector3d v2, Vector3d v3);
	MatrizR(float x11, float x12, float x13, float x21, float x22, float x23, float x31, float x32, float x33);
	MatrizR multiply(MatrizR m);
	Vector3d multiply(Vector3d v);
	string toString();
	// friend MatrizR rotateX(float angle);
	// friend MatrizR rotateY(float angle);
	// friend MatrizR rotateZ(float angle);
};

MatrizR rotateX(float angle);
MatrizR rotateY(float angle);
MatrizR rotateZ(float angle);