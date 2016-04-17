#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include "physics/MatrizR.h"
#include "physics/PhysicsBodyCube.h"
#include "Jet.h"
#include <string>

#include "../GlobalClass.hpp"
#include "../glm/glm.h"

GLMmodel models[1];
#define SPACESHIP_MOD 0

//
//
//void getParentPath(){
//    
//    for (int i = (int)fullPath.length()-1; i>=0 && fullPath[i] != '/'; i--) {
//        fullPath.erase(i,1);
//    }
//}


Jet::Jet(){
	x = 0;
	y = 0;
	z = 0;
	forward = Vector3d(0,0,1);
	up = Vector3d(0,1,0);
	size = 5;
	sizez = 2 * size;
	sizex = 1  * size;
	sizey = 0.4  * size;
	body = PhysicsBodyCube(x, y, z, sizey, sizey, sizey); //sizey cause no time to explain
	yaw = 0;
	pitch = 0;
	roll = 0;
	speed = 0;
	pitchMod = 0;
	rollMod = 0;
	life = 100;
	
	string s =  GlobalClass::instance()->get_path();
    //getParentPath();

	std::string ruta = s + "objects/models/Raider.obj";

	std::cout << "Filepath: " << ruta << std::endl;
	models[SPACESHIP_MOD] = *glmReadOBJ(ruta.c_str());
	glmUnitize(&models[SPACESHIP_MOD]);
	glmVertexNormals(&models[SPACESHIP_MOD], 90.0, GL_TRUE);

    //Load sound effects
	char  rutaThrust[300];
	sprintf(rutaThrust,"%s%s", s.c_str() , "sounds/thrust.wav");
    // cout << rutaThrust << endl;
	gThrust = Mix_LoadWAV( rutaThrust );
	if( gThrust == NULL )
	{
		printf( "Failed to load gThrust sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
	} else {
		Mix_PlayChannel( 0, gThrust, -1 );
	}
}

void Jet::moveJet(){
	float angle = 3.14159 / 32;
	if(pitchMod){
		Vector3d axis = up.cross(forward);
		rotateAxisVec(angle * pitchMod, axis, forward);
		rotateAxisVec(angle * pitchMod, axis, up);
	}
	if(rollMod){
		rotateUpZ(angle * rollMod, forward, up);
	}
	up.normalize();
	forward.normalize();
	z += speed * forward.z;
	x += speed * forward.x;
	y += speed * forward.y;
	// cout << x << " " << y << " " << z << endl;
    
    if(x > abs(5000) || y > abs(5000) || z > abs(5000)){
        
        Vector3d dir;
        dir = Vector3d(-x,-y,-z);
        dir.normalize();
        
        z += speed * dir.z * 2;
        x += speed * dir.x * 2;
        y += speed * dir.y * 2;
    }
    
	body.update(Vector3d(x,y,z));
}

void Jet::paintJet(){
	glPushMatrix();
	{
		glTranslatef(x, y, z);
		glRotatef(-yaw * 180 / 3.14159, 0, 1, 0);
		glRotatef(-pitch * 180 / 3.14159, 1, 0, 0);
		glPushMatrix();
		{
			glRotatef(roll * 180 / 3.14159, 0, 0, 1);
			glScalef(size, size, size);
            glmDraw(&models[SPACESHIP_MOD], GLM_COLOR | GLM_SMOOTH); //GLM_FLAT GLM_SMOOTH
        }
        glPopMatrix();
    }
    glPopMatrix();
    // body.testPaint();
}

void Jet::setSpeed(float s){
	speed = s;
}
float Jet::getSpeed(){
	return speed;
}

void Jet::jetBoost(){
	if (speed <= 0){
		speed = 1;
	} else {
		speed *= 2;
	}
}

void Jet::jetBrake(){
	speed /= 2;
}

void rotateUpZ(float angle, Vector3d forward, Vector3d &up){

	//http://inside.mines.edu/fs_home/gmurray/ArbitraryAxisRotation/

	float u = forward.x;
	float v = forward.y;
	float w = forward.z;
	float x = up.x;
	float y = up.y;
	float z = up.z;

	float oper = (u * x + v * y + w * z) * (1 - cos(angle));
	up.x = u * oper + x * cos(angle) + (v * z - w * y) * sin(angle);
	up.y = v * oper + y * cos(angle) + (w * x - u * z) * sin(angle);
	up.z = w * oper + z * cos(angle) + (u * y - v * x) * sin(angle);

}

void rotateAxisVec(float angle, Vector3d axis, Vector3d &vec){

	//http://inside.mines.edu/fs_home/gmurray/ArbitraryAxisRotation/

	float u = axis.x;
	float v = axis.y;
	float w = axis.z;
	float x = vec.x;
	float y = vec.y;
	float z = vec.z;

	float oper = (u * x + v * y + w * z) * (1 - cos(angle));
	vec.x = u * oper + x * cos(angle) + (v * z - w * y) * sin(angle);
	vec.y = v * oper + y * cos(angle) + (w * x - u * z) * sin(angle);
	vec.z = w * oper + z * cos(angle) + (u * y - v * x) * sin(angle);
}

void Jet::calcDir(){
	yaw = forward.angleFromZinXZ('r');
	Vector3d tempfor = rotateY(yaw).multiply(forward);
	pitch = tempfor.angleFromZinYZ('r');
	Vector3d tempup = rotateX(pitch).multiply(rotateY(yaw).multiply(up));
	roll = tempup.angleFromYinXY('r');
}