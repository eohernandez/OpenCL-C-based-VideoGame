#include "Camera.h"

Camera::Camera(){
	pos = Vector3d();
	dist = 15;
	yawMod = 0;
	pitchMod = 0;
	first = false;
}

void Camera::placeCamera(Jet jet){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Vector3d camerafor = Vector3d(-jet.forward.x, -jet.forward.y, -jet.forward.z);
	camerafor.normalize();
	Vector3d cameraup = Vector3d(jet.up.x, jet.up.y, jet.up.z);
	cameraup.normalize();
	if(!first){
		rotateAxisVec(yawMod, jet.up, camerafor);
		Vector3d axis = camerafor.cross(jet.up);
		axis.normalize();
		rotateAxisVec(-pitchMod, axis, camerafor);
		rotateAxisVec(-pitchMod, axis, cameraup);
		pos.z = jet.z + dist * camerafor.z + dist / 5 * cameraup.z ;
		pos.x = jet.x + dist * camerafor.x + dist / 5 * cameraup.x;
		pos.y = jet.y + dist * camerafor.y + dist / 5 * cameraup.y;
		gluLookAt(pos.x, pos.y, pos.z,
			jet.x + camerafor.x, jet.y + camerafor.y, jet.z + camerafor.z,
			cameraup.x, cameraup.y, cameraup.z);
	} else {
		rotateAxisVec(-yawMod, jet.up, camerafor);
		Vector3d axis = camerafor.cross(jet.up);
		axis.normalize();
		rotateAxisVec(pitchMod, axis, camerafor);
		rotateAxisVec(pitchMod, axis, cameraup);
		pos.z = jet.z + jet.up.z * 10 / 27 + jet.forward.z * 4 / 5;
		pos.x = jet.x + jet.up.x * 10 / 27 + jet.forward.x * 4 / 5;
		pos.y = jet.y + jet.up.y * 10 / 27 + jet.forward.y * 4 / 5;
		gluLookAt(pos.x, pos.y, pos.z,
			pos.x - camerafor.x, pos.y - camerafor.y, pos.z - camerafor.z,
			cameraup.x, cameraup.y, cameraup.z);
	}
}