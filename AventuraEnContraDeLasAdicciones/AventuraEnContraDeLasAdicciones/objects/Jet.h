#pragma once
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <SDL2_mixer/SDL_mixer.h>
#else
#include <GL/glut.h>
#include <SDL2/SDL_mixer.h>
#endif
#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>

#include "physics/MatrizR.h"
#include "physics/PhysicsBodyCube.h"

using namespace std;

class Jet{
public:
	float x;
	float y;
	float z;
	Vector3d forward;
	Vector3d up;
	float size;
	float yaw;
	float pitch;
	float roll;
	float speed;
	int pitchMod;
	int rollMod;
	PhysicsBodyCube body;
	Mix_Chunk *gThrust;
	Jet();
	void moveJet();
	void paintJet();
	void jetBoost();
	void jetBrake();
	void calcDir();
    void setSpeed(float s);
    float getSpeed();
};

void rotateUpZ(float angle, Vector3d forward, Vector3d &up);
void rotateAxisVec(float angle, Vector3d axis, Vector3d &vec);