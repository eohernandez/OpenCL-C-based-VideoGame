#include "Bullet.h"


Bullet::Bullet(){
	pos = Vector3d(0,0,0);
	forward = Vector3d(0,0,0);
	speed = 50;
	life = 100;
	dead = false;
	size = 1;
	body = PhysicsBodyCube(pos, size, size, size);

	string s =  GlobalClass::instance()->get_path();
    // getParentPath();
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
    // getParentPath();
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

void Bullet::paint(){
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	// glScaled(size * 2, size * 2, size * 2);
	// glutSolidSphere(1.0, 20, 20);
	glmDraw(&models[BULLET_MOD], GLM_COLOR | GLM_SMOOTH); 
	// DrawCubeB(0, 0, 0, 1, true);
	glPopMatrix();
	// body.testPaint();
}