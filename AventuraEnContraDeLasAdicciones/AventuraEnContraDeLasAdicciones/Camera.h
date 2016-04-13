#pragma once
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
#include "objects/Jet.h"
#define M_PI 3.14159265358979323846

using namespace std;

class Camera {
public:
	Vector3d pos;
	float dist;
	float yawMod;
	float pitchMod;
	bool first;
	Camera();
	void placeCamera(Jet jet);
};