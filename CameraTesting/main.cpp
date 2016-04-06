#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>

using namespace std;

float centerx = 0, centery = 0, centerz = 0;
float hor = 0, ver = 0;
float camarax = 0, camaray = 0, camaraz = 0, camaradist = 10;

int rotation = 0;

void timer(int v) {
	rotation = (rotation + 10) % 360;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camarax, camaray, camaraz, centerx, centery, centerz, 0, 1, 0);
	glutPostRedisplay();
	glutTimerFunc(50, timer, v);
}

void DrawCube(GLfloat x, GLfloat y, GLfloat z, GLfloat length, bool fill = false){
	
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

	if(fill){
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

void paintJet(float size){

	glPushMatrix();
	glScalef(0.1, 0.1, 0.1);
	glScalef(size, size, size);
	
	//CUERPO

	glPushMatrix();

	glTranslated(0, 0, 2);
	glScaled(1, .5, 5);

	glColor3ub(50,50,50);
	DrawCube(centerx, centery, centerz, 2, true);

	glColor3ub(0,0,0);
	glLineWidth(10);
	DrawCube(centerx, centery, centerz, 2);
	glLineWidth(1);

	glPopMatrix();
	glTranslated(0, 0, 0);

	//ALAS EJE

	glPushMatrix();

	glScaled(4, 0.125, 1);
	glTranslated(0, 0, -0.9);

	glColor3ub(50,50,50);
	DrawCube(centerx, centery, centerz, 2, true);

	glColor3ub(0,0,0);
	glLineWidth(10);
	DrawCube(centerx, centery, centerz, 2);
	glLineWidth(1);

	glPopMatrix();

	//ALAS

	glPushMatrix();

	glTranslated(-4, 0, -1);
	glScaled(1, 0.5, 2);

	glColor3ub(50,50,50);
	DrawCube(centerx, centery, centerz, 2, true);

	glColor3ub(0,0,0);
	glLineWidth(10);
	DrawCube(centerx, centery, centerz, 2);
	glLineWidth(1);

	glPopMatrix();

	glPushMatrix();

	glTranslated(4, 0, -1);
	glScaled(1, 0.5, 2);

	glColor3ub(50,50,50);
	DrawCube(centerx, centery, centerz, 2, true);

	glColor3ub(0,0,0);
	glLineWidth(10);
	DrawCube(centerx, centery, centerz, 2);
	glLineWidth(1);

	glPopMatrix();

	//CABINA

	glPushMatrix();

	glScaled(.8, .5, .8);
	glTranslated(0, 1, -1);

	glColor3ub(0, 0, 255);
	DrawCube(centerx, centery, centerz, 2, true);

	glColor3ub(0,0,0);
	glLineWidth(10);
	DrawCube(centerx, centery, centerz, 2);
	glLineWidth(1);

	glPopMatrix();

	glPopMatrix();
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glColor3ub(0,0,0);

	glPushMatrix();

	//EJES

	glPushMatrix();
	glScaled(100, .05, .05);
	DrawCube(centerx, centery, centerz, 4, true);
	glPopMatrix();

	glPushMatrix();
	glScaled(.05, 100, .05);
	DrawCube(centerx, centery, centerz, 4, true);

	// int count = (int) (20 / 0.05);

	// for (int i = 0; i < count; i += count / 20)
	// {
	// 	DrawCube(centerx + i - count / 2, centery, centerz, 4, true);
	// }

	// for (int i = 0; i < count; i += count / 20)
	// {
	// 	DrawCube(centerx, centery, centerz + i - count / 2, 4, true);
	// }

	glPopMatrix();

	glPushMatrix();
	glScaled(.05, .05, 100);
	DrawCube(centerx, centery, centerz, 4, true);
	glPopMatrix();

	paintJet(10);

	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 10000);
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
	}
}

void init() {
	glClearColor(.9, .9, .9, 1);
	gluLookAt(0, 0, 0, centerx, centery, centerz, 0, 1, 0);
	// IMPORTANTE PARA QUE SE VEA LA PROFUNDIDAD
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

// main(): Initialize GLUT and enter the GLUT event loop.
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Camera_Testing");
	glutReshapeFunc(reshape);
	glutTimerFunc(100, timer, 0);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	init();
	glutMainLoop();
}