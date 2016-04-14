#include "MainMenu.h"


#include "imageloader.hpp"
#include "GlobalClass.hpp"

const int TEXTURE_COUNT=1;
static GLuint texName[TEXTURE_COUNT];


//Makes the image into a texture, and returns the id of the texture
void loadTexture(Image* image,int k)
{
    
    glBindTexture(GL_TEXTURE_2D, texName[k]); //Tell OpenGL which texture to edit
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    //Filtros de ampliacion y redución con cálculo mas cercano no es tan bueno pero es rápido
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    
    //Filtros de ampliacion y redución con cálculo lineal es mejo pero son más calculos
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image->pixels);               //The actual pixel data
}
void initRendering()
{
    //Declaración del objeto Image
    Image* image;
    GLuint i=0;
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glGenTextures(TEXTURE_COUNT, texName); //Make room for our texture
    
    string s =  GlobalClass::instance()->get_path();

    char  ruta[300];
    sprintf(ruta,"%s%s", s.c_str() , "images/AventuraWallpaper.bmp");
    image = loadBMP(ruta);loadTexture(image,i++);
    
    
    delete image;
}


MainMenu::MainMenu(int w, int h){
    
    initRendering();

	glClearColor(.9, .9, .9, 1);
    
    //getParentPath();
    
	this->reshape(w,h);
	state = 0;
	cout << "MainMenu" << endl;
    

    
    
}

void MainMenu::timer(int v){

}

void MainMenu::display(){
    
    //glClearColor(1.0,1.0,1.0,1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    ///*
    
    float minCoord = -50.0f;
    float maxCoord = 50.0f;
    
    //Habilitar el uso de texturas
    glEnable(GL_TEXTURE_2D);
    
    //Elegir la textura del Quads: angulo cambia con el timer
    glBindTexture(GL_TEXTURE_2D, texName[0]);
    
    glBegin(GL_QUADS);
    //Asignar la coordenada de textura 0,0 al vertice
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(minCoord, minCoord, 0);
    //Asignar la coordenada de textura 1,0 al vertice
    glTexCoord2f(1.0f, 0.0f); ///-
    glVertex3f(maxCoord, minCoord, 0);
    //Asignar la coordenada de textura 1,1 al vertice
    glTexCoord2f(1.0f,1.0f); //-
    //glTexCoord2f(1.0f,1.0f);
    //glTexCoord2f(2.0f,5.0f);
    glVertex3f(maxCoord, maxCoord, 0);
    //Asignar la coordenada de textura 0,1 al vertice
    glTexCoord2f(0.0f, 1.0f);
    //glTexCoord2f(0.0f, 5.0f);
    
    glVertex3f(minCoord, maxCoord, 0);
    glEnd();
    
    //*/
    
	//glRectd(-30, -30, 30, 30);

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



