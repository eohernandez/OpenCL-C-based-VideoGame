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
	size = 10;
	yaw = 4;
	pitch = 0;
	roll = 0;
	speed = 0;
	pitchMod = 0;
	rollMod = 0;
    
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

void Jet::paintJet(){

	glPushMatrix();
	{

		glTranslatef(x, y, z);

		glRotatef(-yaw * 180 / 3.14159, 0, 1, 0);
		glRotatef(-pitch * 180 / 3.14159, 1, 0, 0);
		glPushMatrix();
		{
			glRotatef(roll * 180 / 3.14159, 0, 0, 1);
		// glTranslatef(0,0,-size);
			glScalef(0.1, 0.1, 0.1);
			glScalef(size, size, size);

            //modelo
            
            glPushMatrix();
            {
                glScaled(5, 5, 5); 
                glmDraw(&models[SPACESHIP_MOD], GLM_COLOR | GLM_SMOOTH); //GLM_FLAT GLM_SMOOTH
                
            }
            glPopMatrix();
            /*
		//CUERPO

			glPushMatrix();
			{

				glTranslated(0, 0, 2);
				glScaled(1, .5, 5);

				glColor3ub(50,50,50);
				DrawCube(0, 0, 0, 2, true);

				glColor3ub(0,0,0);
				glLineWidth(10);
				DrawCube(0, 0, 0, 2);
				glLineWidth(1);
			}
			glPopMatrix();

		//ALAS EJE

			glPushMatrix();
			{
				glScaled(4, 0.125, 1);
				glTranslated(0, 0, -0.9);

				glColor3ub(50,50,50);
				DrawCube(0, 0, 0, 2, true);

				glColor3ub(0,0,0);
				glLineWidth(10);
				DrawCube(0, 0, 0, 2);
				glLineWidth(1);
			}
			glPopMatrix();

		//ALAS

			glPushMatrix();
			{
				glTranslated(-4, 0, -1);
				glScaled(1, 0.5, 2);

				glColor3ub(50,50,50);
				DrawCube(0, 0, 0, 2, true);

				glColor3ub(0,0,0);
				glLineWidth(10);
				DrawCube(0, 0, 0, 2);
				glLineWidth(1);
			}
			glPopMatrix();

			glPushMatrix();
			{
				glTranslated(4, 0, -1);
				glScaled(1, 0.5, 2);

				glColor3ub(50,50,50);
				DrawCube(0, 0, 0, 2, true);

				glColor3ub(0,0,0);
				glLineWidth(10);
				DrawCube(0, 0, 0, 2);
				glLineWidth(1);
			}
			glPopMatrix();

		//CABINA

			glPushMatrix();
			{
				glScaled(.8, .5, .8);
				glTranslated(0, 1, -1);

				glColor3ub(0, 0, 255);
				DrawCube(0, 0, 0, 2, true);

				glColor3ub(0,0,0);
				glLineWidth(10);
				DrawCube(0, 0, 0, 2);
				glLineWidth(1);

			}
			glPopMatrix();
             
             */

		}
		glPopMatrix();
	}
	glPopMatrix();

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

	// MatrizR rotu, roty, rotx, rotz, rotyy, rotxx;
	// float angley, anglex;
	// Vector3d temp;

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

	// angley = forward.angleFromZinXZ('r');
	// // cout << angley << endl;
	// roty = rotateY(angley);
	// // cout << roty.toString() << endl;
	// rotyy = rotateY(-angley);
	// // cout << rotyy.toString() << endl;
	// temp = roty.multiply(forward);
	// // cout << temp.toString() << endl;
	// anglex = temp.angleFromZinYZ('r');
	// // cout << anglex << endl;
	// rotx = rotateX(anglex);
	// // cout << rotx.toString() << endl;
	// rotxx = rotateX(-anglex);
	// // cout << rotxx.toString() << endl;
	// temp = rotx.multiply(temp);
	// // cout << temp.toString() << endl;
	// rotz = rotateZ(angle);
	// // cout << rotz.toString() << endl;
	// rotu = rotyy.multiply(rotxx.multiply(rotz.multiply(rotx.multiply(roty))));
	// // cout << rotu.toString() << endl;
	// up = rotu.multiply(up);
	// // cout << up.toString() << endl;

}

void rotateAxisVec(float angle, Vector3d axis, Vector3d &vec){

	// MatrizR rot, roty, rotx, rotz, rotyy, rotzz;
	// float angley, anglez;
	// Vector3d temp;

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

	// angley = axis.angleFromXinXZ('r');
	// cout << angley << endl;
	// roty = rotateY(angley);
	// cout << roty.toString() << endl;
	// rotyy = rotateY(-angley);
	// cout << rotyy.toString() << endl;
	// temp = roty.multiply(axis);
	// cout << temp.toString() << endl;
	// anglez = temp.angleFromXinXY('r');
	// cout << anglez << endl;
	// rotz = rotateZ(anglez);
	// cout << rotz.toString() << endl;
	// rotzz = rotateZ(-anglez);
	// cout << rotzz.toString() << endl;
	// temp = rotz.multiply(temp);
	// cout << temp.toString() << endl;
	// rotx = rotateX(angle);
	// cout << rotx.toString() << endl;
	// rot = rotyy.multiply(rotzz.multiply(rotx.multiply(rotz.multiply(roty))));
	// cout << "rot" << rot.toString() << endl;
	// cout << "vec" << vec.toString() << " " ;
	// vec = rot.multiply(vec);
	// cout << vec.toString() << endl << endl;
}

void Jet::calcDir(){
	yaw = forward.angleFromZinXZ('r');
	Vector3d tempfor = rotateY(yaw).multiply(forward);
	pitch = tempfor.angleFromZinYZ('r');
	Vector3d tempup = rotateX(pitch).multiply(rotateY(yaw).multiply(up));
	roll = tempup.angleFromYinXY('r');
}