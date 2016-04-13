#pragma once
#include "Level.h"
#include "Game.h"
#include "Credits.h"

using namespace std;

//Pantalla de menu principal
class MainMenu : public Level{
public:
	MainMenu(int w, int h);
	void timer(int v);
	void display();
	void reshape(int w, int h);
	void keyboard(unsigned char key, int, int);
	void EventLoop(int);
};