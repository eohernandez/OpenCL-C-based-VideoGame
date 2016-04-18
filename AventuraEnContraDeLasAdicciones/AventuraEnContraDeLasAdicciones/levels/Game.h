#pragma once
#include "View.h"
#include "MainMenu.h"
#include "Credits.h"
#include <stack>

#include "../glm/ImageLoader.hpp"

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

#define JOYSTICK_DEAD_ZONE 6000
#define JOYSTICK_MAX_VALUE 32767
#define JOYSTICK_MIN_VALUE -32767

#define NORMAL_MIN_VAL 0
#define NORMAL_MAX_VAL 65534


using namespace std;

//Clase de juego-LO QUE SE TENIA
class Game : public View{
public:
	vector<Bullet> bullets;
	Camera camera;
	Jet jet;
	vector<PhysicsBodyCube> baddie;
	float width;
	float height;
	Game(int w, int h);
	void timer(int v);
	void display();
	void reshape(int w, int h);
	void keyboard(unsigned char key, int, int);
	void EventLoop(int);
	void moveBullets();
	void paintBullets();
	void checkCollision();
	void shoot(int, bool player);
	void paintHUD(float wi, float hi, float wf, float hf);
	void paintGame(float wi, float hi, float wf, float hf);
    void paintBackGroundImage(int x, int y, int z, int rx, int ry, int rz, int size);
    void paintSphere(int x, int y, int z, int size, int texture);
    //float randomFloat(float min, float max);
    //void loadTexture(Image* image,int k);
    //void initRendering();
};

