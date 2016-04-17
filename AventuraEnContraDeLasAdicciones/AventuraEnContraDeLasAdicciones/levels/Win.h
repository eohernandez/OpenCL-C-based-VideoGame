#pragma once
#include "View.h"
#include "MainMenu.h"
#include "Game.h"
#include "Credits.h"
#include "Controls.h"
#include "History.h"
#include "GameOver.h"

using namespace std;

//Pantalla de creditos
class Win : public View{
public:
	Win(int w, int h);
	void timer(int v);
	void display();
	void reshape(int w, int h);
	void keyboard(unsigned char key, int, int);
	void EventLoop(int);
    void writeBigStringWide(GLdouble x, GLdouble y, string s, float size, int r, int g, int b);
};