#include "Bullet.h"


Bullet::Bullet(){
	pos = Vector3d(0,0,0);
	forward = Vector3d(0,0,0);
	speed = 10;
}

Bullet::Bullet(Vector3d pos, Vector3d forward, float speed){
	this->pos.clone(pos);
	this->forward.clone(forward);
	this->speed = speed;
}

void Bullet::move(){
	pos.x += forward.x * speed;
	pos.y += forward.y * speed;
	pos.z += forward.z * speed;
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
	glScaled(0.5, 0.5, 0.5);
	DrawCubeB(0, 0, 0, 1, true);
	glPopMatrix();
}