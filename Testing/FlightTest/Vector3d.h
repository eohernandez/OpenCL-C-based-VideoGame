#include <iostream>
#include <cmath>

using namespace std;

class Vector3d{
public:
	float x;
	float y;
	float z;
	Vector3d();
	Vector3d(float i, float j, float k);
	float dot(Vector3d v3);
	Vector3d cross(Vector3d v3);
	string toString();
	void normalize();
	float angleFromX(char opt);
	float angleFromXinXY(char opt);
	float angleFromXinXZ(char opt);
	float angleFromY(char opt);
	float angleFromYinXY(char opt);
	float angleFromYinYZ(char opt);
	float angleFromZ(char opt);
	float angleFromZinXZ(char opt);
	float angleFromZinYZ(char opt);
};
