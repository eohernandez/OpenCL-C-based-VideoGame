#include <iostream>
#include <cmath>
#include "MatrizR.h"
#define PI 3.14159265


using namespace std;

void rotateUpZ(float angle, Vector3d forward, Vector3d &up){

	MatrizR rotu, roty, rotx, rotz, rotyy, rotxx;
	float angley, anglex;
	Vector3d temp;

	angley = forward.angleFromZinXZ('r');
	// cout << angley << endl;
	roty = rotateY(angley);
	// cout << roty.toString() << endl;
	rotyy = rotateY(-angley);
	// cout << rotyy.toString() << endl;
	temp = roty.multiply(forward);
	// cout << temp.toString() << endl;
	anglex = temp.angleFromZinYZ('r');
	// cout << anglex << endl;
	rotx = rotateX(anglex);
	// cout << rotx.toString() << endl;
	rotxx = rotateX(-anglex);
	// cout << rotxx.toString() << endl;
	temp = rotx.multiply(temp);
	// cout << temp.toString() << endl;
	rotz = rotateZ(angle);
	// cout << rotz.toString() << endl;
	rotu = rotyy.multiply(rotxx.multiply(rotz.multiply(rotx.multiply(roty))));
	// cout << rotu.toString() << endl;
	up = rotu.multiply(up);
	// cout << up.toString() << endl;

}

void rotateAxisVec(float angle, Vector3d axis, Vector3d &vec){

	MatrizR rot, roty, rotx, rotz, rotyy, rotzz;
	float angley, anglez;
	Vector3d temp;

	angley = axis.angleFromXinXZ('r');
	// cout << angley << endl;
	roty = rotateY(angley);
	// cout << roty.toString() << endl;
	rotyy = rotateY(-angley);
	// cout << rotyy.toString() << endl;
	temp = roty.multiply(axis);
	// cout << temp.toString() << endl;
	anglez = temp.angleFromXinXY('r');
	// cout << anglez << endl;
	rotz = rotateZ(anglez);
	// cout << rotz.toString() << endl;
	rotzz = rotateZ(-anglez);
	// cout << rotzz.toString() << endl;
	temp = rotx.multiply(temp);
	// cout << temp.toString() << endl;
	rotx = rotateX(angle);
	// cout << rotx.toString() << endl;
	rot = rotyy.multiply(rotzz.multiply(rotx.multiply(rotz.multiply(roty))));
	// cout << rot.toString() << endl;
	vec = rot.multiply(vec);
	// cout << vec.toString() << endl;

}

void debugLog(Vector3d forward, Vector3d up, Vector3d axis){

	cout << "forward: " << forward.toString() << endl;
	cout << "up: " << up.toString() << endl;
	cout << "angle: " << acos(forward.dot(up)) * 180 / PI << endl;
	cout << "x axis: " << axis.toString() << endl;
	cout << endl;

}

int main(int argc, char const *argv[])
{

	Vector3d forward(0,0,1);
	Vector3d up(0,1,0);
	Vector3d axis = up.cross(forward);

	forward.normalize();
	up.normalize();

	Vector3d v1(0,0,1);
	Vector3d v2(0,1,0);
	Vector3d v3(1,0,0);
	Vector3d v4(0,0,-1);
	Vector3d v5(0,-1,0);
	Vector3d v6(-1,0,0);
	v1.normalize();
	v2.normalize();
	cout << endl;

	// cout << "v1:" << v1.toString() << endl;
	// cout << "angleFromXinXY " << v1.angleFromXinXY('d') << endl;
	// cout << "angleFromXinXZ " << v1.angleFromXinXZ('d') << endl;
	// cout << "angleFromYinXY " << v1.angleFromYinXY('d') << endl;
	// cout << "angleFromYinYZ " << v1.angleFromYinYZ('d') << endl;
	// cout << "angleFromZinXZ " << v1.angleFromZinXZ('d') << endl;
	// cout << "angleFromZinYZ " << v1.angleFromZinYZ('d') << endl;
	// cout << endl;

	// cout << "v2:" << v2.toString() << endl;
	// cout << "angleFromXinXY " << v2.angleFromXinXY('d') << endl;
	// cout << "angleFromXinXZ " << v2.angleFromXinXZ('d') << endl;
	// cout << "angleFromYinXY " << v2.angleFromYinXY('d') << endl;
	// cout << "angleFromYinYZ " << v2.angleFromYinYZ('d') << endl;
	// cout << "angleFromZinXZ " << v2.angleFromZinXZ('d') << endl;
	// cout << "angleFromZinYZ " << v2.angleFromZinYZ('d') << endl;
	// cout << endl;

	// cout << "v3:" << v3.toString() << endl;
	// cout << "angleFromXinXY " << v3.angleFromXinXY('d') << endl;
	// cout << "angleFromXinXZ " << v3.angleFromXinXZ('d') << endl;
	// cout << "angleFromYinXY " << v3.angleFromYinXY('d') << endl;
	// cout << "angleFromYinYZ " << v3.angleFromYinYZ('d') << endl;
	// cout << "angleFromZinXZ " << v3.angleFromZinXZ('d') << endl;
	// cout << "angleFromZinYZ " << v3.angleFromZinYZ('d') << endl;
	// cout << endl;

	// cout << "v4:" << v4.toString() << endl;
	// cout << "angleFromXinXY " << v4.angleFromXinXY('d') << endl;
	// cout << "angleFromXinXZ " << v4.angleFromXinXZ('d') << endl;
	// cout << "angleFromYinXY " << v4.angleFromYinXY('d') << endl;
	// cout << "angleFromYinYZ " << v4.angleFromYinYZ('d') << endl;
	// cout << "angleFromZinXZ " << v4.angleFromZinXZ('d') << endl;
	// cout << "angleFromZinYZ " << v4.angleFromZinYZ('d') << endl;
	// cout << endl;

	// cout << "v5:" << v5.toString() << endl;
	// cout << "angleFromXinXY " << v5.angleFromXinXY('d') << endl;
	// cout << "angleFromXinXZ " << v5.angleFromXinXZ('d') << endl;
	// cout << "angleFromYinXY " << v5.angleFromYinXY('d') << endl;
	// cout << "angleFromYinYZ " << v5.angleFromYinYZ('d') << endl;
	// cout << "angleFromZinXZ " << v5.angleFromZinXZ('d') << endl;
	// cout << "angleFromZinYZ " << v5.angleFromZinYZ('d') << endl;
	// cout << endl;

	// cout << "v6:" << v6.toString() << endl;
	// cout << "angleFromXinXY " << v6.angleFromXinXY('d') << endl;
	// cout << "angleFromXinXZ " << v6.angleFromXinXZ('d') << endl;
	// cout << "angleFromYinXY " << v6.angleFromYinXY('d') << endl;
	// cout << "angleFromYinYZ " << v6.angleFromYinYZ('d') << endl;
	// cout << "angleFromZinXZ " << v6.angleFromZinXZ('d') << endl;
	// cout << "angleFromZinYZ " << v6.angleFromZinYZ('d') << endl;
	// cout << endl;

	MatrizR rotu, rotf, roty, rotx;
	float anglefzxz, anglefzyz;
	Vector3d temp;

	while(true){
		char c;
		cin >> c;
		switch(c){
			case 'w':
			axis = up.cross(forward);
			rotateAxisVec(PI/8, axis, forward);
			rotateAxisVec(PI/8, axis, up);
			break;
			case 's':
			axis = up.cross(forward);
			rotateAxisVec(-PI/8, axis, forward);
			rotateAxisVec(-PI/8, axis, up);
			break;
			case 'a':
			rotateUpZ(PI/8, forward, up);
			break;
			case 'd':
			rotateUpZ(-PI/8, forward, up);
			break;
			default:
			exit(0);
			break;
		}

		forward.normalize();
		up.normalize();
		axis = up.cross(forward);
		debugLog(forward, up, axis);
	}
	
}