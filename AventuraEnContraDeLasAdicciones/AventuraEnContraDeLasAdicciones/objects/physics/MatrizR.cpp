#include "MatrizR.h"

MatrizR::MatrizR(){
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			mat[i][j] = 0;
		}
	}
}

MatrizR::MatrizR(Vector3d v1, Vector3d v2, Vector3d v3){
	mat[0][0] = v1.x;
	mat[0][1] = v1.y;
	mat[0][2] = v1.z;
	mat[1][0] = v2.x;
	mat[1][1] = v2.y;
	mat[1][2] = v2.z;
	mat[2][0] = v3.x;
	mat[2][1] = v3.y;
	mat[2][2] = v3.z;
}

MatrizR::MatrizR(float x11, float x12, float x13, float x21, float x22, float x23, float x31, float x32, float x33){
	mat[0][0] = x11;
	mat[0][1] = x12;
	mat[0][2] = x13;
	mat[1][0] = x21;
	mat[1][1] = x22;
	mat[1][2] = x23;
	mat[2][0] = x31;
	mat[2][1] = x32;
	mat[2][2] = x33;
}

MatrizR MatrizR::multiply(MatrizR m){
	MatrizR res;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			res.mat[i][j] = Vector3d(mat[i][0], mat[i][1], mat[i][2]).dot(Vector3d(m.mat[0][j], m.mat[1][j], m.mat[2][j]));
		}
	}
	return res;
}
Vector3d MatrizR::multiply(Vector3d v){
	float temp[3];
	for (int i = 0; i < 3; i++){
		temp[i] = Vector3d(mat[i][0], mat[i][1], mat[i][2]).dot(v);
	}
	return Vector3d(temp[0], temp[1], temp[2]);
}

string MatrizR::toString(){
	string res = "["; //]
	for (int i = 0; i < 3; i++)
	{
		res += "[" + to_string(mat[i][0]) + "," + to_string(mat[i][1]) + "," + to_string(mat[i][2]) + "]";
	}
	res += "]"; //[
	return res;
}

MatrizR rotateX(float angle){
	Vector3d x(1,0,0);
	Vector3d y(0,cos(angle),-sin(angle));
	Vector3d z(0,sin(angle),cos(angle));
	return MatrizR(x,y,z);
}

MatrizR rotateY(float angle){
	Vector3d x(cos(angle),0,sin(angle));
	Vector3d y(0,1,0);
	Vector3d z(-sin(angle),0,cos(angle));
	return MatrizR(x,y,z);
}

MatrizR rotateZ(float angle){
	Vector3d x(cos(angle),-sin(angle),0);
	Vector3d y(sin(angle),cos(angle),0);
	Vector3d z(0,0,1);
	return MatrizR(x,y,z);
}
