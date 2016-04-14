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
#else
#include <GL/glut.h>

#endif
#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <vector>
#include "Camera.h"
#include "objects/Jet.h"
#include "objects/Bullet.h"
#include "glm/glm.h"
#include "levels/Level.h"
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

//Apuntador de clase Level, padre de todos los estados, LO QUE SE TENIA ESTA EN Game.cpp
Level *level;
int state; //Referencia del estado actual

int width = 500, height = 500;

void getParentPath(){
    
    for (int i = (int)fullPath.length()-1; i>=0 && fullPath[i] != '/'; i--) {
        fullPath.erase(i,1);
    }
}


//Checa el estado en el que se encuentra, si el nivel pide otro estado, se elimina y se crea un nuevo estado
void checkState(){
    if(level->state != state){
        switch(level->state){

            case MAIN_MENU:
            delete level;
            level = new MainMenu(width, height);
            state = MAIN_MENU;
            break;

            case GAME:
            delete level;
            level = new Game(width, height);
            state = GAME;
            break;

            case CREDITS:
            delete level;
            level = new Credits(width, height);
            state = CREDITS;
            break;
        }
    }
}

//------------------------------Funciones de Glut, todas se redireccionan a los estados

void timer(int v) {
    checkState();
    level->timer(v);
    glutTimerFunc(50, timer, v);
}

void display() {
    level->display();
}

void reshape(int w, int h) {
    width = w;
    height = h;
    level->reshape(w,h);
}

void keyboard(unsigned char key, int, int) {
    level->keyboard(key, 0, 0);
}

void EventLoop(int);
void EventLoop(int){
    level->EventLoop(0);
    {
        // SDL_Event sdlEvent;

        // while( SDL_PollEvent( &sdlEvent ) ) {
        //     switch( sdlEvent.type ) {

        //         case SDL_CONTROLLERDEVICEADDED:
        //         cout << "AddController( sdlEvent.cdevice );" << endl;
        //         break;

        //         case SDL_CONTROLLERDEVICEREMOVED:
        //         cout << "RemoveController( sdlEvent.cdevice );" << endl;
        //         break;

        //         case SDL_CONTROLLERBUTTONDOWN:
        //         case SDL_CONTROLLERBUTTONUP:
        //         cout << "OnControllerButton( sdlEvent.cbutton );" << endl;
        //         break;

        //         case SDL_CONTROLLERAXISMOTION:
        //         cout << "OnControllerAxis( sdlEvent.caxis );" << endl;
        //         break;

        //         case SDL_JOYAXISMOTION:
        //     // if(abs(sdlEvent.jaxis.value) > JOYSTICK_DEAD_ZONE){
        //     //  printf("Joystick %d axis %d value: %d\n",
        //     //      sdlEvent.jaxis.which,
        //     //      sdlEvent.jaxis.axis, sdlEvent.jaxis.value);
        //     // }
        //     //Motion on controller 0
        //         if( sdlEvent.jaxis.which == 0 ) {                        
        //         //Z axis motion
        //             if( sdlEvent.jaxis.axis ==  0)  {
        //             //Below of dead zone
        //                 if( sdlEvent.jaxis.value < -JOYSTICK_DEAD_ZONE ) {
        //                     jet.rollMod = -1;
        //                 }
        //             //Above of dead zone
        //                 else if( sdlEvent.jaxis.value > JOYSTICK_DEAD_ZONE ) {
        //                     jet.rollMod =  1;
        //                 }
        //                 else {
        //                     jet.rollMod = 0;
        //                 }
        //             }
        //         //Y axis motion
        //             else if( sdlEvent.jaxis.axis == 1 ) {
        //             //Left of dead zone
        //                 if( sdlEvent.jaxis.value < -JOYSTICK_DEAD_ZONE ) {
        //                     jet.pitchMod = 1;
        //                 }
        //             //Right of dead zone
        //                 else if( sdlEvent.jaxis.value > JOYSTICK_DEAD_ZONE ) {
        //                     jet.pitchMod =  -1;
        //                 }
        //                 else {
        //                     jet.pitchMod = 0;
        //                 }
        //         //Yaw camera motion
        //             } else if( sdlEvent.jaxis.axis ==  2)   {
        //             //Below of dead zone
        //                 if( sdlEvent.jaxis.value < -JOYSTICK_DEAD_ZONE ) {
        //                     camera.yawMod = (M_PI / 2.3) * (sdlEvent.jaxis.value + JOYSTICK_DEAD_ZONE) / (JOYSTICK_MAX_VALUE - JOYSTICK_DEAD_ZONE);
        //                 }
        //             //Above of dead zone
        //                 else if( sdlEvent.jaxis.value > JOYSTICK_DEAD_ZONE ) {
        //                     camera.yawMod = (M_PI / 2.3) * (sdlEvent.jaxis.value - JOYSTICK_DEAD_ZONE) / (JOYSTICK_MAX_VALUE - JOYSTICK_DEAD_ZONE);
        //                 }
        //                 else {
        //                     camera.yawMod = 0;
        //                 }
        //             }
        //         //Y axis motion
        //             else if( sdlEvent.jaxis.axis == 3 ) {
        //             //Left of dead zone
        //                 if( sdlEvent.jaxis.value < -JOYSTICK_DEAD_ZONE ) {
        //                     camera.pitchMod = (M_PI / 2.3) * (sdlEvent.jaxis.value + JOYSTICK_DEAD_ZONE) / (JOYSTICK_MAX_VALUE - JOYSTICK_DEAD_ZONE);
        //                 }
        //             //Right of dead zone
        //                 else if( sdlEvent.jaxis.value > JOYSTICK_DEAD_ZONE ) {
        //                     camera.pitchMod = (M_PI / 2.3) * (sdlEvent.jaxis.value - JOYSTICK_DEAD_ZONE) / (JOYSTICK_MAX_VALUE - JOYSTICK_DEAD_ZONE);
        //                 }
        //                 else {
        //                     camera.pitchMod = 0;
        //                 }
        //             } else if( sdlEvent.jaxis.axis == 4 ) {
        //             //Full Trigger
        //                 if( sdlEvent.jaxis.value == JOYSTICK_MAX_VALUE ) {
        //                     shooting = true;
        //                     shoot(0);
        //                 } else {
        //                     shooting = false;
        //                 }
        //             }else {
        //                 if(abs(sdlEvent.jaxis.value) > JOYSTICK_DEAD_ZONE){
        //                     printf("Joystick %d axis %d value: %d\n",
        //                         sdlEvent.jaxis.which,
        //                         sdlEvent.jaxis.axis, sdlEvent.jaxis.value);
        //                 }
        //             }
        //         }
        //         break;
        //         case SDL_JOYHATMOTION:
        //         printf("Joystick %d hat %d value:",
        //             sdlEvent.jhat.which, sdlEvent.jhat.hat);
        //         if (sdlEvent.jhat.value == SDL_HAT_CENTERED)
        //             printf(" centered");
        //         if (sdlEvent.jhat.value & SDL_HAT_UP)
        //             printf(" up");
        //         if (sdlEvent.jhat.value & SDL_HAT_RIGHT)
        //             printf(" right");
        //         if (sdlEvent.jhat.value & SDL_HAT_DOWN)
        //             printf(" down");
        //         if (sdlEvent.jhat.value & SDL_HAT_LEFT)
        //             printf(" left");
        //         printf("\n");
        //         break;
        //         case SDL_JOYBALLMOTION:
        //         printf("Joystick %d ball %d delta: (%d,%d)\n",
        //             sdlEvent.jball.which,
        //             sdlEvent.jball.ball, sdlEvent.jball.xrel, sdlEvent.jball.yrel);
        //         break;
        //         case SDL_JOYBUTTONDOWN:
        //     // printf("Joystick %d button %d down\n",
        //     //  sdlEvent.jbutton.which, sdlEvent.jbutton.button);
        //         if( sdlEvent.jaxis.which == 0 ){  
        //             switch(sdlEvent.jbutton.button){
        //                 case 0:
        //                 jet.jetBoost();
        //                 break;
        //                 case 1:
        //                 jet.jetBrake();
        //                 break;
        //                 case 3:
        //                 camera.first = !camera.first;
        //                 break;
        //                 default:
        //                 printf("Joystick %d button %d down\n",
        //                     sdlEvent.jbutton.which, sdlEvent.jbutton.button);
        //                 break;
        //             }
        //         } else{
        //             printf("Joystick %d button %d down\n",
        //                 sdlEvent.jbutton.which, sdlEvent.jbutton.button);
        //         }
        //         break;
        //     // case SDL_JOYBUTTONUP:
        //     // printf("Joystick %d button %d up\n",
        //     //  sdlEvent.jbutton.which, sdlEvent.jbutton.button);
        //     // break;
        //         case SDL_KEYDOWN:
        //         if ((sdlEvent.key.keysym.sym != SDLK_ESCAPE) && (sdlEvent.key.keysym.sym != SDLK_AC_BACK)) {
        //             break;
        //         }
        //         /* Fall through to signal quit */
        // // YOUR OTHER EVENT HANDLING HERE

        //     }
        // }
    }
    glutTimerFunc(10, EventLoop, 0);
}

//------------------------------Fin funciones de Glut

//Iniciacion del Juego

GlobalClass *GlobalClass::s_instance = 0;

void init() {
    
    getParentPath();
    
    GlobalClass::instance()->set_path(fullPath);
    SDL_Init(SDL_INIT_GAMECONTROLLER);
    for (int i = 0; i < SDL_NumJoysticks(); ++i)
    {
        joy = SDL_JoystickOpen(0);
    }
    level = new MainMenu(width, height);
    state = MAIN_MENU;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Aventura En Contra De Las Adicciones");
    glutReshapeFunc(reshape);
    glutTimerFunc(50, timer, 0);
    glutTimerFunc(10, EventLoop, 0);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
}