#include "Vector3d.h"

#define PI 3.14159265

Vector3d::Vector3d(){
	x = 0;
	y = 0;
	z = 0;
}

Vector3d::Vector3d(float i, float j, float k){
	x = i;
	y = j;
	z = k;
}

float Vector3d::dot(Vector3d v3){
	float i = x * v3.x;
	float j = y * v3.y;
	float k = z * v3.z;
	return i + j + k;
}

Vector3d Vector3d::cross(Vector3d v3){
	float i = y * v3.z - z * v3.y;
	float j = z * v3.x - x * v3.z;
	float k = x * v3.y - y * v3.x;
	return Vector3d(i, j, k);
}

string Vector3d::toString(){
	return "[" + to_string(x) + "," + to_string(y) + "," + to_string(z) + "]";
}

void Vector3d::normalize(){
	// x = round(x * 10000)/10000;
	// y = round(y * 10000)/10000;
	// z = round(z * 10000)/10000;
	float length = sqrt((x * x) + (y * y) + (z * z));
	x = x / length;
	y = y / length;
	z = z / length;
}

float Vector3d::angleFromX(char opt){
	Vector3d axis(1,0,0);
	if(opt == 'd'){
		return acos(dot(axis)) * 180 / PI;
	}
	else{
		return acos(dot(axis));
	}
}

float Vector3d::angleFromXinXY(char opt){
	Vector3d axis(1,0,0);
	if(x==0 && y==0){
		return 0;
	}
	Vector3d vec_in_xy(x,y,0);
	vec_in_xy.normalize();
	float res;
	if(opt == 'd'){
		res = acos(vec_in_xy.dot(axis)) * 180 / PI;
	}
	else{
		res = acos(vec_in_xy.dot(axis));
	}
	if(y<0){
		res = -res;
	}
	return res;
}

float Vector3d::angleFromXinXZ(char opt){
	Vector3d axis(1,0,0);
	if(x==0 && z==0){
		return 0;
	}
	Vector3d vec_in_xz(x,0,z);
	vec_in_xz.normalize();
	float res;
	if(opt == 'd'){
		res = acos(vec_in_xz.dot(axis)) * 180 / PI;
	}
	else{
		res = acos(vec_in_xz.dot(axis));
	}
	if(z<0){
		res = -res;
	}
	return res;
}

float Vector3d::angleFromY(char opt){
	Vector3d axis(0,1,0);
	if(opt == 'd'){
		return acos(dot(axis)) * 180 / PI;
	}
	else{
		return acos(dot(axis));
	}
}

float Vector3d::angleFromYinXY(char opt){
	Vector3d axis(0,1,0);
	if(x==0 && y==0){
		return 0;
	}
	Vector3d vec_in_xy(x,y,0);
	vec_in_xy.normalize();
	float res;
	if(opt == 'd'){
		res = acos(vec_in_xy.dot(axis)) * 180 / PI;
	}
	else{
		res = acos(vec_in_xy.dot(axis));
	}
	if(x>0){
		res = -res;
	}
	return res;
}

float Vector3d::angleFromYinYZ(char opt){
	Vector3d axis(0,1,0);
	if(y==0 && z==0){
		return 0;
	}
	Vector3d vec_in_yz(0,y,z);
	vec_in_yz.normalize();
	float res;
	if(opt == 'd'){
		res = acos(vec_in_yz.dot(axis)) * 180 / PI;
	}
	else{
		res = acos(vec_in_yz.dot(axis));
	}
	if(z>0){
		res = -res;
	}
	return res;
}

float Vector3d::angleFromZ(char opt){
	Vector3d axis(0,0,1);
	if(opt == 'd'){
		return acos(dot(axis)) * 180 / PI;
	}
	else{
		return acos(dot(axis));
	}
}

float Vector3d::angleFromZinXZ(char opt){
	Vector3d axis(0,0,1);
	if(x==0 && z==0){
		return 0;
	}
	Vector3d vec_in_xz(x,0,z);
	vec_in_xz.normalize();
	float res;
	if(opt == 'd'){
		res = acos(vec_in_xz.dot(axis)) * 180 / PI;
	}
	else{
		res = acos(vec_in_xz.dot(axis));
	}
	if(x>0){
		res = -res;
	}
	return res;
}

float Vector3d::angleFromZinYZ(char opt){
	Vector3d axis(0,0,1);
	if(y==0 && z==0){
		return 0;
	}
	Vector3d vec_in_yz(0,y,z);
	vec_in_yz.normalize();
	float res;
	if(opt == 'd'){
		res = acos(vec_in_yz.dot(axis)) * 180 / PI;
	}
	else{
		res = acos(vec_in_yz.dot(axis));
	}
	if(y<0){
		res = -res;
	}
	return res;
}