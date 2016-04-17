#pragma once
#include "View.h"
#include "MainMenu.h"
#include "Game.h"

using namespace std;

//Pantalla de creditos
class Credits : public View{
public:
	Credits(int w, int h);
	void timer(int v);
	void display();
	void reshape(int w, int h);
	void keyboard(unsigned char key, int, int);
	void EventLoop(int);
};