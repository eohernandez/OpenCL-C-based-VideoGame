#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <vector>
#include "Jet.h"
#define PI 3.14159265
#define JOYSTICK_DEAD_ZONE 8000


using namespace std;

void debugLog(Vector3d forward, Vector3d up, Vector3d axis);

struct Camera
{
	Vector3d pos;
	float dist = 5;
};

struct Bullet
{
	Vector3d pos;
	Vector3d forward;
	float speed = 10;
};

vector<Bullet> bullets;

Camera camera;
Jet jet;

SDL_GameController *controller = nullptr;
SDL_Joystick *joy = nullptr;

void placeCamera(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.pos.z = jet.z + camera.dist * -jet.forward.z + jet.up.z;
	camera.pos.x = jet.x + camera.dist * -jet.forward.x + jet.up.x;
	camera.pos.y = jet.y + camera.dist * -jet.forward.y + jet.up.y;
	gluLookAt(camera.pos.x, camera.pos.y, camera.pos.z, jet.x, jet.y, jet.z, jet.up.x, jet.up.y, jet.up.z);
	// gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);
}

void moveBullets(){
	for (int i = 0; i < bullets.size(); i++){
		Bullet it = bullets[i];
		it.pos.x += it.forward.x * it.speed;
		it.pos.y += it.forward.y * it.speed;
		it.pos.z += it.forward.z * it.speed;
		bullets[i] = it;
	}
}

void timer(int v) {
	moveBullets();
	jet.calcDir();
	jet.moveJet();
	placeCamera();
	glutPostRedisplay();
	// Vector3d axis = jet.up.cross(jet.forward);
	// debugLog(jet.forward, jet.up, axis);
	glutTimerFunc(50, timer, v);
}

void DrawCube(GLfloat x, GLfloat y, GLfloat z, GLfloat length, bool fills = false, bool fill = false){
	
	GLfloat halflenght = length / 2;
	GLfloat vertices[] = {
		// front face
		x - halflenght, y + halflenght, z + halflenght,
		x + halflenght, y + halflenght, z + halflenght,
		x + halflenght, y - halflenght, z + halflenght,
		x - halflenght, y - halflenght, z + halflenght,
		// back face
		x - halflenght, y + halflenght, z - halflenght,
		x + halflenght, y + halflenght, z - halflenght,
		x + halflenght, y - halflenght, z - halflenght,
		x - halflenght, y - halflenght, z - halflenght,
		// left face
		x - halflenght, y + halflenght, z + halflenght,
		x - halflenght, y + halflenght, z - halflenght,
		x - halflenght, y - halflenght, z - halflenght,
		x - halflenght, y - halflenght, z + halflenght,
		// right face
		x + halflenght, y + halflenght, z + halflenght,
		x + halflenght, y + halflenght, z - halflenght,
		x + halflenght, y - halflenght, z - halflenght,
		x + halflenght, y - halflenght, z + halflenght,
		// top face
		x - halflenght, y + halflenght, z + halflenght,
		x - halflenght, y + halflenght, z - halflenght,
		x + halflenght, y + halflenght, z - halflenght,
		x + halflenght, y + halflenght, z + halflenght,
		// bottom face
		x - halflenght, y - halflenght, z + halflenght,
		x - halflenght, y - halflenght, z - halflenght,
		x + halflenght, y - halflenght, z - halflenght,
		x + halflenght, y - halflenght, z + halflenght,
	};

	if(fills){
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);

		glEnableClientState(GL_VERTEX_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glDrawArrays(GL_QUADS, 0, 24);

		glDisableClientState(GL_VERTEX_ARRAY);
	}
	else{
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);

		glEnableClientState(GL_VERTEX_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glDrawArrays(GL_QUADS, 0, 24);

		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void paintBullets(){
	for (int i = 0; i < bullets.size(); i++){
		Bullet it = bullets[i];
		glPushMatrix();
		glTranslatef(it.pos.x, it.pos.y, it.pos.z);
		glScaled(0.5, 0.5, 0.5);
		DrawCube(0, 0, 0, 1, true);
		glPopMatrix();
	}
}

void paintGridAround(int count){

	// CARA 1

	for (int i = 0; i < count; ++i)
	{
		glPushMatrix();
		glTranslatef(i - count / 2, 0, count / 2);
		glScaled(.05, 100, .05);
		DrawCube(0, 0, 0, 4, true);
		glPopMatrix();
	}

	for (int i = 0; i < count; ++i)
	{
		glPushMatrix();
		glTranslatef(0, i - count / 2, count / 2);
		glScaled(100, .05, .05);
		DrawCube(0, 0, 0, 4, true);
		glPopMatrix();
	}

	// CARA 2

	for (int i = 0; i < count; ++i)
	{
		glPushMatrix();
		glTranslatef(i - count / 2, 0, -count / 2);
		glScaled(.05, 100, .05);
		DrawCube(0, 0, 0, 4, true);
		glPopMatrix();
	}

	for (int i = 0; i < count; ++i)
	{
		glPushMatrix();
		glTranslatef(0, i - count / 2, -count / 2);
		glScaled(100, .05, .05);
		DrawCube(0, 0, 0, 4, true);
		glPopMatrix();
	}

	// CARA 3

	for (int i = 0; i < count; ++i)
	{
		glPushMatrix();
		glTranslatef(i - count / 2, count / 2, 0);
		glScaled(.05, .05, 100);
		DrawCube(0, 0, 0, 4, true);
		glPopMatrix();
	}

	for (int i = 0; i < count; ++i)
	{
		glPushMatrix();
		glTranslatef(0, count / 2, i - count / 2);
		glScaled(100, .05, .05);
		DrawCube(0, 0, 0, 4, true);
		glPopMatrix();
	}

	// CARA 4

	for (int i = 0; i < count; ++i)
	{
		glPushMatrix();
		glTranslatef(i - count / 2, -count / 2, 0);
		glScaled(.05, .05, 100);
		DrawCube(0, 0, 0, 4, true);
		glPopMatrix();
	}

	for (int i = 0; i < count; ++i)
	{
		glPushMatrix();
		glTranslatef(0, -count / 2, i - count / 2);
		glScaled(100, .05, .05);
		DrawCube(0, 0, 0, 4, true);
		glPopMatrix();
	}

	// CARA 5

	for (int i = 0; i < count; ++i)
	{
		glPushMatrix();
		glTranslatef(count / 2, i - count / 2, 0);
		glScaled(.05, .05, 100);
		DrawCube(0, 0, 0, 4, true);
		glPopMatrix();
	}

	for (int i = 0; i < count; ++i)
	{
		glPushMatrix();
		glTranslatef(count / 2, 0, i - count / 2);
		glScaled(.05, 100, .05);
		DrawCube(0, 0, 0, 4, true);
		glPopMatrix();
	}

	// CARA 6

	for (int i = 0; i < count; ++i)
	{
		glPushMatrix();
		glTranslatef(-count / 2, i - count / 2, 0);
		glScaled(.05, .05, 100);
		DrawCube(0, 0, 0, 4, true);
		glPopMatrix();
	}

	for (int i = 0; i < count; ++i)
	{
		glPushMatrix();
		glTranslatef(-count / 2, 0, i - count / 2);
		glScaled(.05, 100, .05);
		DrawCube(0, 0, 0, 4, true);
		glPopMatrix();
	}
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glColor3ub(0,0,0);

	glPushMatrix();
	glScaled(100, .05, .05);
	DrawCube(0, 0, 0, 4, true);
	glPopMatrix();

	glPushMatrix();
	glScaled(.05, 100, .05);
	DrawCube(0, 0, 0, 4, true);
	glPopMatrix();

	glPushMatrix();
	glScaled(.05, .05, 100);
	DrawCube(0, 0, 0, 4, true);
	glPopMatrix();

	paintGridAround(400);

	//DrawCube(0, 0, 0, 4, true);

	paintBullets();

	jet.paintJet();

	glutSwapBuffers();
}

void reshape(int w, int h) {
	if(w>h){
		glViewport(0 + (w-h)/2, 0, h, h);
	} else {
		glViewport(0, 0 + (h-w)/2, w, w);
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// glFrustum(-5, 5, -5, 5, 1, 100);
	gluPerspective(60, 1, 1, 10000);
	placeCamera();
	// glMatrixMode(GL_MODELVIEW);
	// glLoadIdentity();
	// gluLookAt(5, 5, -5, 0, 0, 0, 0, 1, 0);
}

void debugLog(Vector3d forward, Vector3d up, Vector3d axis){

	cout << "forward: " << forward.toString() << endl;
	cout << "up: " << up.toString() << endl;
	cout << "angle: " << acos(up.dot(forward)) * 180 / PI << endl;
	cout << "x axis: " << axis.toString() << endl;
	cout << endl;

}

void keyboard(unsigned char key, int, int) {
	// float radv = (jet.ver + 15) * 3.1416 / 180;
	Vector3d axis;
	axis = jet.up.cross(jet.forward);
	float angle = PI/16;
	switch(key) {
		case 'w':
		rotateAxisVec(angle, axis, jet.forward);
		rotateAxisVec(angle, axis, jet.up);
		break;
		case 's':
		rotateAxisVec(-angle, axis, jet.forward);
		rotateAxisVec(-angle, axis, jet.up);
		break;
		case 'a':
		rotateUpZ(-angle, jet.forward, jet.up);
		break;
		case 'd':
		rotateUpZ(angle, jet.forward, jet.up);
		break;
		// case 'w': 
		// jet.ver = (int)( jet.ver - 10) % 360;
		// break;
		// case 'a': 
		// jet.hor = (int)( jet.hor + ((int) 10 * cos(radv)/abs(cos(radv)))) % 360;
		// break;
		// case 's': 
		// jet.ver = (int)( jet.ver + 10) % 360;
		// break;
		// case 'd': 
		// jet.hor = (int)( jet.hor - (10 * cos(radv)/abs(cos(radv)))) % 360;
		// break;
		case 'q': 
		jet.jetBoost();
		break;
		case 'e': 
		jet.jetBrake();
		break;
	}
	jet.up.normalize();
	jet.forward.normalize();
	axis = jet.up.cross(jet.forward);
	debugLog(jet.forward, jet.up, axis);

}

void init() {
	glClearColor(.9, .9, .9, 1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	camera.pos = Vector3d(0,0,0);
	SDL_Init(SDL_INIT_GAMECONTROLLER);
	for (int i = 0; i < SDL_NumJoysticks(); ++i)
	{
		joy = SDL_JoystickOpen(0);
		// if(SDL_IsGameController(i)){
		// 	controller = SDL_GameControllerOpen(i);
		// 	cout << SDL_GameControllerMapping(controller) << endl;
		// 	break;
		// }
	}
}

void EventLoop(int);
bool shooting = false;

void shoot(int);

void shoot(int){
	Bullet bu;
	bu.pos = Vector3d(jet.x, jet.y, jet.z);
	bu.forward = jet.forward;
	bullets.push_back(bu);
	if (shooting)
	{
		glutTimerFunc(10, shoot, 0);
	}
}

void EventLoop(int)
{
	SDL_Event sdlEvent;

	while( SDL_PollEvent( &sdlEvent ) ) {
		switch( sdlEvent.type ) {

			case SDL_CONTROLLERDEVICEADDED:
			cout << "AddController( sdlEvent.cdevice );" << endl;
			break;

			case SDL_CONTROLLERDEVICEREMOVED:
			cout << "RemoveController( sdlEvent.cdevice );" << endl;
			break;

			case SDL_CONTROLLERBUTTONDOWN:
			case SDL_CONTROLLERBUTTONUP:
			cout << "OnControllerButton( sdlEvent.cbutton );" << endl;
			break;

			case SDL_CONTROLLERAXISMOTION:
			cout << "OnControllerAxis( sdlEvent.caxis );" << endl;
			break;

			case SDL_JOYAXISMOTION:
			// if(abs(sdlEvent.jaxis.value) > JOYSTICK_DEAD_ZONE){
			// 	printf("Joystick %d axis %d value: %d\n",
			// 		sdlEvent.jaxis.which,
			// 		sdlEvent.jaxis.axis, sdlEvent.jaxis.value);
			// }
			//Motion on controller 0
			if( sdlEvent.jaxis.which == 0 )	{                        
                //X axis motion
				if( sdlEvent.jaxis.axis == 1 ) {
                    //Left of dead zone
					if( sdlEvent.jaxis.value < -JOYSTICK_DEAD_ZONE ) {
						jet.pitchMod = 1;
					}
                    //Right of dead zone
					else if( sdlEvent.jaxis.value > JOYSTICK_DEAD_ZONE ) {
						jet.pitchMod =  -1;
					}
					else {
						jet.pitchMod = 0;
					}
				}
             	//Y axis motion
				else if( sdlEvent.jaxis.axis == 2 )	{
                    //Below of dead zone
					if( sdlEvent.jaxis.value < -JOYSTICK_DEAD_ZONE ) {
						jet.rollMod = -1;
					}
                    //Above of dead zone
					else if( sdlEvent.jaxis.value > JOYSTICK_DEAD_ZONE ) {
						jet.rollMod =  1;
					}
					else {
						jet.rollMod = 0;
					}
				} else if( sdlEvent.jaxis.axis == 4 ) {
                    //Full Trigger
					if( sdlEvent.jaxis.value == 32767 ) {
						shooting = true;
						shoot(0);
					} else {
						shooting = false;
					}
				}else {
					if(abs(sdlEvent.jaxis.value) > JOYSTICK_DEAD_ZONE){
						printf("Joystick %d axis %d value: %d\n",
							sdlEvent.jaxis.which,
							sdlEvent.jaxis.axis, sdlEvent.jaxis.value);
					}
				}
			}
			break;
			case SDL_JOYHATMOTION:
			printf("Joystick %d hat %d value:",
				sdlEvent.jhat.which, sdlEvent.jhat.hat);
			if (sdlEvent.jhat.value == SDL_HAT_CENTERED)
				printf(" centered");
			if (sdlEvent.jhat.value & SDL_HAT_UP)
				printf(" up");
			if (sdlEvent.jhat.value & SDL_HAT_RIGHT)
				printf(" right");
			if (sdlEvent.jhat.value & SDL_HAT_DOWN)
				printf(" down");
			if (sdlEvent.jhat.value & SDL_HAT_LEFT)
				printf(" left");
			printf("\n");
			break;
			case SDL_JOYBALLMOTION:
			printf("Joystick %d ball %d delta: (%d,%d)\n",
				sdlEvent.jball.which,
				sdlEvent.jball.ball, sdlEvent.jball.xrel, sdlEvent.jball.yrel);
			break;
			case SDL_JOYBUTTONDOWN:
			// printf("Joystick %d button %d down\n",
			// 	sdlEvent.jbutton.which, sdlEvent.jbutton.button);
			if( sdlEvent.jaxis.which == 0 ){  
				switch(sdlEvent.jbutton.button){
					case 0:
					jet.jetBoost();
					break;
					case 1:
					jet.jetBrake();
					break;
					default:
					printf("Joystick %d button %d down\n",
						sdlEvent.jbutton.which, sdlEvent.jbutton.button);
					break;
				}
			} else{
				printf("Joystick %d button %d down\n",
					sdlEvent.jbutton.which, sdlEvent.jbutton.button);
			}
			break;
			// case SDL_JOYBUTTONUP:
			// printf("Joystick %d button %d up\n",
			// 	sdlEvent.jbutton.which, sdlEvent.jbutton.button);
			// break;
			case SDL_KEYDOWN:
			if ((sdlEvent.key.keysym.sym != SDLK_ESCAPE) && (sdlEvent.key.keysym.sym != SDLK_AC_BACK)) {
				break;
			}
                /* Fall through to signal quit */
        // YOUR OTHER EVENT HANDLING HERE

		}
	}
	glutTimerFunc(10, EventLoop, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Flight_Testing");
	glutReshapeFunc(reshape);
	glutTimerFunc(50, timer, 0);
	glutTimerFunc(10, EventLoop, 0);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	init();
	glutMainLoop();
}