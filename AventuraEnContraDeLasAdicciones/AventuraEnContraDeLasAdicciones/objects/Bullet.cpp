#include "Bullet.h"


Bullet::Bullet(){
	pos = Vector3d(0,0,0);
	forward = Vector3d(0,0,0);
	speed = 10;
	life = 100;
	dead = false;
	size = 0.5;
	body = PhysicsBodyCube(pos, size, size, size);

	string s =  GlobalClass::instance()->get_path();
    //getParentPath();
	std::string ruta = s + "objects/models/webtrcc.obj";
	// std::cout << "Filepath: " << ruta << std::endl;
	models[BULLET_MOD] = *glmReadOBJ(ruta.c_str());
	glmUnitize(&models[BULLET_MOD]);
	glmVertexNormals(&models[BULLET_MOD], 90.0, GL_TRUE);

	//Load sound effects
	char  rutaSaber[300];
	sprintf(rutaSaber,"%s%s", s.c_str() , "sounds/blast.wav");
    // cout << rutaSaber << endl;
	gSaber = Mix_LoadWAV( rutaSaber );
	if( gSaber == NULL )
	{
		printf( "Failed to load gSaber sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
	} else {
		Mix_PlayChannel( 1, gSaber, 0 );
	}
}

Bullet::Bullet(Vector3d pos, Vector3d forward, float speed){
	this->pos.clone(pos);
	this->forward.clone(forward);
	this->speed = speed;
	life = 100;
	dead = false;
	size = 0.5;
	body = PhysicsBodyCube(pos, size, size, size);

	string s =  GlobalClass::instance()->get_path();
    //getParentPath();
	std::string ruta = s + "objects/models/webtrcc.obj";
	// std::cout << "Filepath: " << ruta << std::endl;
	models[BULLET_MOD] = *glmReadOBJ(ruta.c_str());
	glmUnitize(&models[BULLET_MOD]);
	glmVertexNormals(&models[BULLET_MOD], 90.0, GL_TRUE);
}

void Bullet::move(){
	pos.x += forward.x * speed;
	pos.y += forward.y * speed;
	pos.z += forward.z * speed;
	life--;
	if(!life){
		dead = true;
	}
	body.update(pos);
}

void DrawCubeB(GLfloat x, GLfloat y, GLfloat z, GLfloat length, bool fills = false, bool fill = false){
	
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

void Bullet::paint(){
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	// glScaled(size * 2, size * 2, size * 2);
	glmDraw(&models[BULLET_MOD], GLM_COLOR | GLM_SMOOTH); 
	// DrawCubeB(0, 0, 0, 1, true);
	glPopMatrix();
}