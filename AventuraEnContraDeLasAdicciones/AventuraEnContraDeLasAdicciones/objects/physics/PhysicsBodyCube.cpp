#include "PhysicsBodyCube.h"

PhysicsBodyCube::PhysicsBodyCube(){
	maxv = Vector3d(0,0,0);
	maxPast = Vector3d(0,0,0);
	minv = Vector3d(0,0,0);
	minPast = Vector3d(0,0,0);
}

PhysicsBodyCube::PhysicsBodyCube(float x, float y, float z, float sizex, float sizey, float sizez){
	maxv = Vector3d(x + sizex, y + sizey, z + sizez);
	maxPast = Vector3d(x + sizex, y + sizey, z + sizez);
	minv = Vector3d(x - sizex, y - sizey, z - sizez);
	minPast = Vector3d(x - sizex, y - sizey, z - sizez);
}

PhysicsBodyCube::PhysicsBodyCube(Vector3d pos, float sizex, float sizey, float sizez){
	maxv = Vector3d(pos.x + sizex, pos.y + sizey, pos.z + sizez);
	maxPast = Vector3d(pos.x + sizex, pos.y + sizey, pos.z + sizez);
	minv = Vector3d(pos.x - sizex, pos.y - sizey, pos.z - sizez);
	minPast = Vector3d(pos.x - sizex, pos.y - sizey, pos.z - sizez);
}

void PhysicsBodyCube::update(Vector3d pos){
	Vector3d size = Vector3d((maxv.x - minv.x) / 2, (maxv.y - minv.y) / 2, (maxv.z - minv.z) / 2);
	maxPast.clone(maxv);
	minPast.clone(minv);
	maxv.clone(Vector3d(pos.x + size.x, pos.y + size.y, pos.z + size.z));
	minv.clone(Vector3d(pos.x - size.x, pos.y - size.y, pos.z - size.z));
}

bool PhysicsBodyCube::collides(PhysicsBodyCube body){
	return ((maxv.x >= body.minv.x and minv.x <= body.maxv.x)
		and (maxv.y >= body.minv.y and minv.y <= body.maxv.y)
		and (maxv.z >= body.minv.z and minv.z <= body.maxv.z));
}

bool PhysicsBodyCube::collidesContinuos(PhysicsBodyCube body){
	return (
		((max(maxv.x, maxPast.x) >= min(body.minv.x, body.minPast.x) 
			and min(minv.x, minPast.x) <= max(body.maxv.x, body.maxPast.x)))
		and ((max(maxv.y, maxPast.y) >= min(body.minv.y, body.minPast.y)
			and min(minv.y, minPast.y) <= max(body.maxv.y, body.maxPast.y)))
		and ((max(maxv.z, maxPast.z) >= min(body.minv.z, body.minPast.z) 
			and min(minv.z, minPast.z) <= max(body.maxv.z, body.maxPast.z))));
}