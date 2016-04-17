//
//  main.cpp
//  AventuraEnContraDeLasAdicciones
//
//  Created by Enrique Hernandez on 3/13/16.
//  Copyright © 2016 Enrique. All rights reserved.
//
#pragma once
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <SDL2_mixer/SDL_mixer.h>
#else
#include <GL/glut.h>

#endif
#include <iostream>
#include <fstream>
#include <cmath>
#include <SDL2/SDL.h>
#include <vector>
#include "Camera.h"
#include "objects/Jet.h"
#include "objects/Bullet.h"
#include "glm/glm.h"
#include "levels/View.h"
#include "levels/MainMenu.h"
#include "levels/Game.h"
#include "levels/Credits.h"
#include "GlobalClass.hpp"


#define JOYSTICK_DEAD_ZONE 8000
#define JOYSTICK_MAX_VALUE 32767
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define MAIN_MENU 0
#define GAME 1
#define CREDITS 2

string fullPath = __FILE__;


using namespace std;

//Variables para SDL
SDL_GameController *controller;
SDL_Joystick *joy;

//Apuntador de clase View, padre de todos los estados, LO QUE SE TENIA ESTA EN Game.cpp
View *view;
int state; //Referencia del estado actual

int width = 1200, height = 1000;

void getParentPath(){

    for (int i = (int)fullPath.length()-1; i>=0 && fullPath[i] != '/'; i--) {
        fullPath.erase(i,1);
    }
}


//Checa el estado en el que se encuentra, si el nivel pide otro estado, se elimina y se crea un nuevo estado
void checkState(){
    if(view->state != state){
        switch(view->state){

            case MAIN_MENU:
            delete view;
            view = new MainMenu(width, height);
            state = MAIN_MENU;
            break;

            case GAME:
            delete view;
            view = new Game(width, height);
            state = GAME;
            break;

            case CREDITS:
            delete view;
            view = new Credits(width, height);
            state = CREDITS;
            break;
        }
    }
}

//------------------------------Funciones de Glut, todas se redireccionan a los estados

void timer(int v) {
    checkState();
    view->timer(v);
    glutTimerFunc(50, timer, v);
}

void display() {
    view->display();
}

void reshape(int w, int h) {
    width = w;
    height = h;
    view->reshape(w,h);
}

void keyboard(unsigned char key, int, int) {
    view->keyboard(key, 0, 0);
}

void EventLoop(int);
void EventLoop(int){

    view->EventLoop(0);

    glutTimerFunc(10, EventLoop, 0);
}

//------------------------------Fin funciones de Glut

//Iniciacion del Juego

GlobalClass *GlobalClass::s_instance = 0;

void init() {
    getParentPath();
    
    
    GlobalClass::instance()->set_path(fullPath);
    GlobalClass::instance()->initRendering();
    SDL_Init(SDL_INIT_GAMECONTROLLER  | SDL_INIT_AUDIO);
    for (int i = 0; i < SDL_NumJoysticks(); ++i)
    {
        joy = SDL_JoystickOpen(0);
    }
     //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }

    view = new MainMenu(width, height);
    state = MAIN_MENU;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(width, height);
    glutCreateWindow("Aventura En Contra De Las Adicciones");
    glutReshapeFunc(reshape);
    glutTimerFunc(50, timer, 0);
    glutTimerFunc(10, EventLoop, 0);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
}