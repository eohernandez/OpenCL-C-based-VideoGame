#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
#include "PhysicsBodyCube.h"
#define CUBESIZE 9

using namespace std;

float centerx = 0, centery = 0, centerz = 0;
float hor = 0, ver = 0;
float camarax = 0, camaray = 0, camaraz = 0, camaradist = 10;

float vel = .01;

struct Cube
{
	int id;
	PhysicsBodyCube body;
	Vector3d pos;
	float size;
};

Cube cubes[CUBESIZE];

Vector3d cubespos[CUBESIZE] = {
	Vector3d(0,0,0),
	Vector3d(5,5,-5),
	Vector3d(5,5,5),
	Vector3d(5,-5,-5),
	Vector3d(5,-5,5),
	Vector3d(-5,5,-5),
	Vector3d(-5,5,5),
	Vector3d(-5,-5,-5),
	Vector3d(-5,-5,5)
};

float cubessize[CUBESIZE] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

int rotation = 0;

void timer(int v) {
	cubes[0].pos.x += vel;
	cubes[0].pos.x *= 2;
	cubes[0].pos.z += vel;
	cubes[0].pos.z *= 2;
	cubes[0].pos.y += vel;
	cubes[0].pos.y *= 2;
	cubes[0].body.update(cubes[0].pos);
	for (int i = 1; i < CUBESIZE; ++i)
	{
		if(cubes[0].body.collides(cubes[i].body)){
			vel *= -1;
			cubes[0].pos.x = 0;
			cubes[0].pos.z = 0;
			cubes[0].pos.y = 0;
		} else if (cubes[0].body.collidesContinuos(cubes[i].body)) {
			vel *= -1;
			cubes[0].pos.x = 0;
			cubes[0].pos.z = 0;
			cubes[0].pos.y = 0;
		}
	}
	rotation = (rotation + 10) % 360;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camarax, camaray, camaraz, centerx, centery, centerz, 0, 1, 0);
	glutPostRedisplay();
	glutTimerFunc(100, timer, v);
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


	glPushMatrix();
	{
	//EJES
		glPushMatrix();
		{
			glScaled(100, .05, .05);
			glColor3ub(0,0,0);
			glutSolidCube(4);
			glColor3ub(100,100,100);
			glutWireCube(4);
		}
		glPopMatrix();
		{
			glPushMatrix();
			glScaled(.05, 100, .05);
			glColor3ub(0,0,0);
			glutSolidCube(4);
			glColor3ub(100,100,100);
			glutWireCube(4);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glScaled(.05, .05, 100);
			glColor3ub(0,0,0);
			glutSolidCube(4);
			glColor3ub(100,100,100);
			glutWireCube(4);
		}
		glPopMatrix();

		for (int i = 0; i < CUBESIZE; ++i)
		{
			glPushMatrix();
			{
				glTranslatef(cubes[i].pos.x, cubes[i].pos.y, cubes[i].pos.z);
				glScalef(cubes[i].size * 2, cubes[i].size * 2, cubes[i].size * 2);
				glColor3ub(0,0,0);
				glutSolidCube(1);
				glColor3ub(100,100,100);
				glutWireCube(1);
			}
			glPopMatrix();
		}
	}
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, ((double)w)/h, 1, 10000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camaraz = -camaradist * cos(hor * 3.1416 / 180) * cos(ver * 3.1416 / 180);
	camarax = camaradist * sin(hor * 3.1416 / 180) * cos(ver * 3.1416 / 180);
	camaray = camaradist * sin(ver * 3.1416 / 180);
	gluLookAt(camarax, camaray, camaraz, centerx, centery, centerz, 0, 1, 0);
}

void keyboard(unsigned char key, int, int) {
	switch(key) {
		case 'w': 
		ver = ((int) ver + 10) % 360;
		camaraz = -camaradist * cos(hor * 3.1416 / 180) * cos(ver * 3.1416 / 180);
		camarax = camaradist * sin(hor * 3.1416 / 180) * cos(ver * 3.1416 / 180);
		camaray = camaradist * sin(ver * 3.1416 / 180);
		break;
		case 'a': 
		hor = ((int) hor - 10) % 360;
		camaraz = -camaradist * cos(hor * 3.1416 / 180) * cos(ver * 3.1416 / 180);
		camarax = camaradist * sin(hor * 3.1416 / 180) * cos(ver * 3.1416 / 180);
		camaray = camaradist * sin(ver * 3.1416 / 180);
		break;
		case 's': 
		ver = ((int) ver - 10) % 360;
		camaraz = -camaradist * cos(hor * 3.1416 / 180) * cos(ver * 3.1416 / 180);
		camarax = camaradist * sin(hor * 3.1416 / 180) * cos(ver * 3.1416 / 180);
		camaray = camaradist * sin(ver * 3.1416 / 180);
		break;
		case 'd': 
		hor = ((int) hor + 10) % 360;
		camaraz = -camaradist * cos(hor * 3.1416 / 180) * cos(ver * 3.1416 / 180);
		camarax = camaradist * sin(hor * 3.1416 / 180) * cos(ver * 3.1416 / 180);
		camaray = camaradist * sin(ver * 3.1416 / 180);
		break;
		case 'q': 
		camaradist++;
		camaraz = -camaradist * cos(hor * 3.1416 / 180) * cos(ver * 3.1416 / 180);
		camarax = camaradist * sin(hor * 3.1416 / 180) * cos(ver * 3.1416 / 180);
		camaray = camaradist * sin(ver * 3.1416 / 180);
		break;
		case 'e': 
		camaradist--;
		camaraz = -camaradist * cos(hor * 3.1416 / 180) * cos(ver * 3.1416 / 180);
		camarax = camaradist * sin(hor * 3.1416 / 180) * cos(ver * 3.1416 / 180);
		camaray = camaradist * sin(ver * 3.1416 / 180);
		break;
		case 'p':
		break;
	}
}

void init() {
	glClearColor(.9, .9, .9, 1);
	gluLookAt(0, 0, 0, centerx, centery, centerz, 0, 1, 0);
	// IMPORTANTE PARA QUE SE VEA LA PROFUNDIDAD
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	for (int i = 0; i < CUBESIZE; ++i)
	{
		Cube cube;
		cube.id = i;
		cube.body = PhysicsBodyCube(cubespos[i], cubessize[i], cubessize[i], cubessize[i]);
		cube.pos = cubespos[i];
		cube.size = cubessize[i];
		cubes[i] = cube;
		cubes[i].body.update(cubes[i].pos);

	}
}

// main(): Initialize GLUT and enter the GLUT event loop.
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Physics_Testing");
	glutReshapeFunc(reshape);
	glutTimerFunc(100, timer, 0);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	init();
	glutMainLoop();
}