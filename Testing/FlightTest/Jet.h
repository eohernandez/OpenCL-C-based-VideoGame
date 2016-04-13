#include <iostream>
#include <cmath>
#include "MatrizR.h"

using namespace std;

class Jet{
public:
	float x;
	float y;
	float z;
	Vector3d forward;
	Vector3d up;
	float size;
	float yaw;
	float pitch;
	float roll;
	float speed;
	Jet();
	void moveJet();
	void paintJet();
	void jetBoost();
	void jetBrake();
	void calcDir();
	int pitchMod;
	int rollMod;
};

void rotateUpZ(float angle, Vector3d forward, Vector3d &up);
void rotateAxisVec(float angle, Vector3d axis, Vector3d &vec);