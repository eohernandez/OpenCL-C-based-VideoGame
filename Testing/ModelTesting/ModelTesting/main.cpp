//
//  main.cpp
//  ModelTesting
//
//  Created by Enrique Hernandez on 4/11/16.
//  Copyright © 2016 Enrique. All rights reserved.
//

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <cstring>
#include <math.h>

#include "glm.h"

#include <iostream>

//DEFINES

#define MODEL_COUNT 1
#define SPACESHIP_MOD 0

using namespace std;
string fullPath = __FILE__;

GLMmodel models[MODEL_COUNT];

int screenWidth = 800, screenHeight = 700;
double camera_zoom = 15;
int current_direction = 0;
int glWin, minPathLength = 0, myPathLength = 0;
float backgroundColor           [] = {255.0/255.0,255.0/255.0,255.0/255.0};

//Text rasters
GLdouble xRaster, yRaster;
typedef enum {MENU, INSTRUCTIONS, PLAY, GAMEOVER} screens;
int game_screen = MENU;
int angulo =0;


void timer (int v){
    
    angulo = (angulo + 10) % 360;
    glutPostRedisplay();
    glutTimerFunc(100, timer, 1);
}


void drawMaze(){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    int bannerHeight = 100;
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 25, 0, 0, 0, 0, 1, 0);
    glViewport(0, 0, screenWidth, screenHeight-bannerHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)screenWidth/(GLfloat)screenHeight, 1.0, 60.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 20, 0, 0, 0, 0, 1, 0);
    
    glPushMatrix();
    //glRotatef(45, 1, 1, 1);
    
    glPushMatrix();
    glTranslated(0, 0, 0);
    glRotated(angulo, 0, 1, 0);
    glScaled(5, 5, 5);      //
    glmDraw(&models[SPACESHIP_MOD], GLM_COLOR | GLM_SMOOTH); //GLM_FLAT GLM_SMOOTH
    glPopMatrix();
    
    /*
     *            GLM_NONE     -  render with only vertices
     *            GLM_FLAT     -  render with facet normals
     *            GLM_SMOOTH   -  render with vertex normals
     *            GLM_TEXTURE  -  render with texture coords
     *            GLM_COLOR    -  render with colors (color material)
     *            GLM_MATERIAL -  render with materials
     *            GLM_COLOR and GLM_MATERIAL should not both be specified.
     *            GLM_FLAT and GLM_SMOOTH should not both be specified.
     */
    
    glPopMatrix();
}

void init(){
    
    //General settings
    glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], 1.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    
    //SPACESHIP
    std::string ruta = fullPath + "objects/SpaceShip.obj";
    std::cout << "Filepath: " << ruta << std::endl;
    models[SPACESHIP_MOD] = *glmReadOBJ(ruta.c_str());
    glmUnitize(&models[SPACESHIP_MOD]);
    glmVertexNormals(&models[SPACESHIP_MOD], 90.0, GL_TRUE);
    
}

void display(){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawMaze();
    glutSwapBuffers();
}

void reshape(int w, int h){
    
    screenWidth = w;
    screenHeight = h;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 1.0, 60.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 25, 0, 0, 0, 0, 1, 0);
    
}

void getParentPath(){
    
    for (int i = (int)fullPath.length()-1; i>=0 && fullPath[i] != '/'; i--) {
        fullPath.erase(i,1);
    }
}

int main(int argc, char *argv[]){
    
    //Find root path for files
    getParentPath();
    glutInit(&argc,argv);
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize(screenWidth,screenHeight);
    glWin = glutCreateWindow("Uso de Modelos con glm");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(100, timer, 1);
    glutMainLoop();
    return EXIT_SUCCESS;
}

