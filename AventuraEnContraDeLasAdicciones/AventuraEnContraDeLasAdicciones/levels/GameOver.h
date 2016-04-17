#pragma once
#include "View.h"
#include "MainMenu.h"
#include "Game.h"
#include "Credits.h"
#include "Controls.h"
#include "History.h"

using namespace std;

//Pantalla de creditos
class GameOver : public View{
public:
	GameOver(int w, int h);
	void timer(int v);
	void display();
	void reshape(int w, int h);
	void keyboard(unsigned char key, int, int);
	void EventLoop(int);
};