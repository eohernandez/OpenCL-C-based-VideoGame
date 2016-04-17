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

#include <vector>
#include "../Camera.h"
#include "../objects/Jet.h"
#include "../objects/Bullet.h"
#include "../glm/glm.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

class View {
public:
	int state;
	virtual void timer(int v) = 0;
	virtual void display() = 0;
	virtual void reshape(int w, int h) = 0;
	virtual void keyboard(unsigned char key, int, int) = 0;
	virtual void EventLoop(int) = 0;
};