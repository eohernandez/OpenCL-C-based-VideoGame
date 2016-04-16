#pragma once
#include "Level.h"
#include "MainMenu.h"
#include "Credits.h"
#include <stack>

using namespace std;

//Clase de juego-LO QUE SE TENIA
class Game : public Level{
public:
	vector<Bullet> bullets;
	Camera camera;
	Jet jet;
	vector<PhysicsBodyCube> baddie;
	bool shooting;
	Game(int w, int h);
	void timer(int v);
	void display();
	void reshape(int w, int h);
	void keyboard(unsigned char key, int, int);
	void EventLoop(int);
	void moveBullets();
	void paintBullets();
	void paintBaddies();
	void checkCollision();
	void shoot(int);
};