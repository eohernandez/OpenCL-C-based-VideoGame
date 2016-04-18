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

#define M_PI 3.14159265358979323846
#include "physics/Vector3d.h"
#include "physics/PhysicsBodyCube.h"
#include "../GlobalClass.hpp"
#include "../glm/glm.h"

#define BULLET_MOD 0

using namespace std;

class Bullet {
public:
	Vector3d pos;
	GLMmodel models[1];
	Vector3d forward;
	float speed;
	PhysicsBodyCube body;
	int life;
	bool dead;
	bool player;
	float size;
	Mix_Chunk *gSaber;
	Bullet();
	Bullet(Vector3d pos, Vector3d forward, float speed);
	void move();
	void paint();
    ~Bullet();
};