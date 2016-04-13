#include "MainMenu.h"

MainMenu::MainMenu(int w, int h){
	glClearColor(.9, .9, .9, 1);
	this->reshape(w,h);
	state = 0;
	cout << "MainMenu" << endl;
}

void MainMenu::timer(int v){

}

void MainMenu::display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glRectd(-30, -30, 30, 30);

	glutSwapBuffers();
}

void MainMenu::reshape(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-50, 50, -50, 50);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void MainMenu::keyboard(unsigned char key, int, int){
	state = 1;
	switch(key) {
	}
}

void MainMenu::EventLoop(int){

}