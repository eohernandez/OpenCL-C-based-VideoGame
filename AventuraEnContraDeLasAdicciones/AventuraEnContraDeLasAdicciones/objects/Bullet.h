#pragma once
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#define M_PI 3.14159265358979323846
#include "physics/Vector3d.h"
#include "physics/PhysicsBodyCube.h"

using namespace std;

class Bullet {
public:
	Vector3d pos;
	Vector3d forward;
	float speed;
	PhysicsBodyCube body;
	Bullet();
	Bullet(Vector3d pos, Vector3d forward, float speed);
	void move();
	void paint();
};