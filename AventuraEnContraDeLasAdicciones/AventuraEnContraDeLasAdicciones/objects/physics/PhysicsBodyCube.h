#pragma once
#include <iostream>
#include <cmath>
#include "Vector3d.h"
#include <algorithm>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

class PhysicsBodyCube {
public:
	Vector3d maxv;
	Vector3d maxPast;
	Vector3d minv;
	Vector3d minPast;
	PhysicsBodyCube();
	PhysicsBodyCube(float x, float y, float z, float sizex, float sizey, float sizez);
	PhysicsBodyCube(Vector3d pos, float sizex, float sizey, float sizez);
	void update(Vector3d pos);
	bool collides(PhysicsBodyCube body);
	bool collidesContinuos(PhysicsBodyCube body);
	void testPaint();
};