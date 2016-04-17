#pragma once
#include "View.h"
#include "MainMenu.h"
#include "Game.h"
#include "Credits.h"

using namespace std;

//Pantalla de creditos
class Controls : public View{
public:
	Controls(int w, int h);
	void timer(int v);
	void display();
	void reshape(int w, int h);
	void keyboard(unsigned char key, int, int);
	void EventLoop(int);
};