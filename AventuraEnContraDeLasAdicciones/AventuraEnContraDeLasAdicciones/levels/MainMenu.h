#pragma once
#include "View.h"
#include "Game.h"
#include "Credits.h"
#include "../glm/ImageLoader.hpp"
#include "../GlobalClass.hpp"



#ifdef __APPLE__

#define LEFT_STICK_HORIZONTAL       0
#define LEFT_STICK_VERTICAL         1
#define LT_AXIS                     2
#define RIGHT_STICK_HORIZONTAL      3
#define RIGHT_STICK_VERTICAL        4
#define RT_AXIS                     5

#define BUTTON_A                    0
#define BUTTON_B                    1
#define BUTTON_X                    2
#define BUTTON_Y                    3
#define BUTTON_LB                   4
#define BUTTON_RB                   5
#define BUTTON_LEFT_STICK           6
#define BUTTON_RIGHT_STICK          7
#define BUTTON_START                8
#define BUTTON_BACK                 9
#define BUTTON_XBOX                 10

#else

#define LEFT_STICK_HORIZONTAL       0
#define LEFT_STICK_VERTICAL         1
#define LT_AXIS                     5
#define RIGHT_STICK_HORIZONTAL      2
#define RIGHT_STICK_VERTICAL        3
#define RT_AXIS                     4

#define BUTTON_A                    0
#define BUTTON_B                    1
#define BUTTON_X                    2
#define BUTTON_Y                    3
#define BUTTON_LB                   4
#define BUTTON_RB                   5
#define BUTTON_LEFT_STICK           9
#define BUTTON_RIGHT_STICK          10
#define BUTTON_START                7
#define BUTTON_BACK                 6
#define BUTTON_XBOX                 8

#endif

using namespace std;

//Pantalla de menu principal
class MainMenu : public View{
public:
	MainMenu(int w, int h);
	void timer(int v);
	void display();
	void reshape(int w, int h);
	void keyboard(unsigned char key, int, int);
	void EventLoop(int);
};