#include "Game.h"
#include <random>
#include <stack>

Game* game;

std::random_device rd;

#define PLANETS 10
#define EVILS 10
#define HEALTHS 3
#define MODELS 6

GLMmodel gameModels[MODELS];

struct GameObject{
	int x;
	int y;
	int z;
	int texture;
	int size;
};

int evilsAlive = EVILS;
GameObject planets[PLANETS];
GameObject evils[EVILS];
PhysicsBodyCube evilsBody[EVILS];
bool evilscount[EVILS];
GameObject healths[HEALTHS];
bool healthsTaken[HEALTHS];
PhysicsBodyCube healthsBody[HEALTHS];
stack<int> killBullets;
bool gamePause = false;

void paintModel(int tex, int x, int y, int z, int size);

float randomFloat(float min, float max)
{
    // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(min , max); // guaranteed unbiased
    
    int random_integer = uni(rng);
    
    return random_integer * 1.0 ;
    
}
int pos_or_neg(){

	return randomFloat(0, 10) < 5 ? -1 : 1;
}

void Game::moveBullets(){
	for (int i = 0; i < bullets.size(); i++){
		Bullet it = bullets[i];
		it.move();
		bullets[i] = it;
	}
}

void Game::paintBullets(){
	for (int i = 0; i < bullets.size(); i++){
		Bullet it = bullets[i];
		if(!it.dead){
			it.paint();
		}
	}
}

void assignBodysEvil(){
	for (int i = 0; i < EVILS; ++i)
	{
		switch(evils[i].texture){
			case 0:
			evilsBody[i] = PhysicsBodyCube(
				evils[i].x, evils[i].y, evils[i].z, 
				0.5 * evils[i].size, 2 * evils[i].size, 0.5 * evils[i].size);
			break;
			case 1:
			evilsBody[i] = PhysicsBodyCube(
				evils[i].x, evils[i].y, evils[i].z, 
				0.2 * evils[i].size, 0.2 * evils[i].size, 2 * evils[i].size);
			break;
			case 2:
			evilsBody[i] = PhysicsBodyCube(
				evils[i].x, evils[i].y, evils[i].z, 
				1 * evils[i].size, 0.2 * evils[i].size, 1 * evils[i].size);
			break;
			case 3:
			evilsBody[i] = PhysicsBodyCube(
				evils[i].x, evils[i].y, evils[i].z, 
				1 * evils[i].size, 0.6 * evils[i].size, 2 * evils[i].size);
			break;
		}
		evilsBody[i].update(Vector3d(evils[i].x, evils[i].y, evils[i].z));
	}
}

void assignBodysHealth(){
	for (int i = 0; i < HEALTHS; ++i)
	{
		switch(healths[i].texture){
			case 4:
			healthsBody[i] = PhysicsBodyCube(
				healths[i].x, healths[i].y, healths[i].z, 
				2 * healths[i].size, 2 * healths[i].size, 2 * healths[i].size);
			break;
			case 5:
			healthsBody[i] = PhysicsBodyCube(
				healths[i].x, healths[i].y, healths[i].z, 
				0.8 * healths[i].size, 2 * healths[i].size, 0.8 * healths[i].size);
			break;
		}
		healthsBody[i].update(Vector3d(healths[i].x, healths[i].y, healths[i].z));
	}
}

void initStructs(){

	for (int i = 0; i < PLANETS; i++) {
		planets[i].x = randomFloat(5000, 9000) * pos_or_neg();
		planets[i].y = randomFloat(5000, 9000) * pos_or_neg();
		planets[i].z = randomFloat(5000, 9000) * pos_or_neg();
		planets[i].size = randomFloat(10, 20);
		planets[i].texture = randomFloat(2, 3);
	}

	for (int i = 0; i < EVILS; i++) {
		evils[i].x = randomFloat(500, 4500) * pos_or_neg();
		evils[i].y = randomFloat(500, 4500) * pos_or_neg();
		evils[i].z = randomFloat(500, 4500) * pos_or_neg();
		evils[i].size = randomFloat(100, 200);
		evils[i].texture = randomFloat(0, 3);
		evilscount[i] = true;
	}

	for (int i = 0; i < HEALTHS; i++) {
		healths[i].x = randomFloat(500, 4500) * pos_or_neg();
		healths[i].y = randomFloat(500, 4500) * pos_or_neg();
		healths[i].z = randomFloat(500, 4500) * pos_or_neg();
		healths[i].size = randomFloat(100, 200);
		healths[i].texture = randomFloat(4, 5);
		healthsTaken[i] = true;
	}

	assignBodysEvil();

	assignBodysHealth();

	string s =  GlobalClass::instance()->get_path();
    //getParentPath();
	string ruta = s + "objects/models/beerbottle_belgian.obj";
	cout << "Filepath: " << ruta << std::endl;
	gameModels[0] = *glmReadOBJ(ruta.c_str());
	glmUnitize(&gameModels[0]);
	glmVertexNormals(&gameModels[0], 90.0, GL_TRUE);

	ruta = s + "objects/models/cigarette.obj";
	cout << "Filepath: " << ruta << std::endl;
	gameModels[1] = *glmReadOBJ(ruta.c_str());
	glmUnitize(&gameModels[1]);
	glmVertexNormals(&gameModels[1], 90.0, GL_TRUE);

	ruta = s + "objects/models/weed.obj";
	cout << "Filepath: " << ruta << std::endl;
	gameModels[2] = *glmReadOBJ(ruta.c_str());
	glmUnitize(&gameModels[2]);
	glmVertexNormals(&gameModels[2], 90.0, GL_TRUE);

	ruta = s + "objects/models/free_injector_OBJ.obj";
	cout << "Filepath: " << ruta << std::endl;
	gameModels[3] = *glmReadOBJ(ruta.c_str());
	glmUnitize(&gameModels[3]);
	glmVertexNormals(&gameModels[3], 90.0, GL_TRUE);

	ruta = s + "objects/models/apple.obj";
	cout << "Filepath: " << ruta << std::endl;
	gameModels[4] = *glmReadOBJ(ruta.c_str());
	glmUnitize(&gameModels[4]);
	glmVertexNormals(&gameModels[4], 90.0, GL_TRUE);

	ruta = s + "objects/models/water.obj";
	cout << "Filepath: " << ruta << std::endl;
	gameModels[5] = *glmReadOBJ(ruta.c_str());
	glmUnitize(&gameModels[5]);
	glmVertexNormals(&gameModels[5], 90.0, GL_TRUE);
}

string formato(int t){
    
    string seconds = (((t/10)%60) < 10) ? ("0" + std::to_string((t/10)%60)) : (std::to_string((t/10)%60));
    
    return std::to_string(((t/10)/60)%60) + ":" + seconds + "." + std::to_string(t%10);
}


void Game::shoot(int, bool player){
	Bullet bu;
	bu.player = player;
	bu.forward = jet.forward;
	Vector3d axis = jet.up.cross(jet.forward);
	bu.pos = Vector3d(jet.x + 2 * axis.x, jet.y + 2 * axis.y, jet.z + 2 * axis.z);
	bullets.push_back(bu);
	bu.pos = Vector3d(jet.x - 2 * axis.x, jet.y - 2 * axis.y, jet.z - 2 * axis.z);
	bullets.push_back(bu);
}

Game::Game(int w, int h){
	state = 1;
    
    GlobalClass::instance()->resetGameDefaults();
    
	glClearColor(.9, .9, .9, 1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	game = this;
	this->reshape(w,h);
	cout << "gamme" << endl;
    //initRendering();
    evilsAlive = EVILS;
	initStructs();

}

void Game::checkCollision(){
	for (int i = 0; i < bullets.size(); ++i)
	{
		if(!bullets[i].dead){
			if(bullets[i].player){
				for (int j = 0; j < EVILS; ++j)
				{
					if (evilscount[j] && bullets[i].body.collidesContinuos(evilsBody[j]))
					{
                        GlobalClass::instance()->updatePoints(10);
                        evilsAlive--;
						killBullets.push(i);
						bullets[i].dead = true;
						evilscount[j] = false;
					}
				}
			}
		} else {
			killBullets.push(i);
		}
	}
	while(!killBullets.empty()){
		bullets.erase(bullets.begin() + killBullets.top());
        
		killBullets.pop();
	}
}

void Game::timer(int v){

    if(!gamePause){
        GlobalClass::instance()->updateTimer(0.5);
        checkCollision();
        moveBullets();
        jet.calcDir();
        jet.moveJet();
        if(bullets.size()){
            //cout << bullets.size() << endl;
        }
    }
    if(GlobalClass::instance()->getTimer() < 0){
        state = 4;
    }
    if(evilsAlive <= 0){
        
        state = 5;
    }
    
    glutPostRedisplay();

}

void Game::paintBackGroundImage(int x, int y, int z, int rx, int ry, int rz, int size){

	size = size / 2;


	float minCoord = size * -1.0;
	float maxCoord = size * 1.0;

	glColor3f(255, 255, 255);


	glPushMatrix();
	{
		glRotatef(90, rx, ry, rz);
		glTranslatef(x, y, z);


        //Habilitar el uso de texturas
		glEnable(GL_TEXTURE_2D);

		GLuint tex0 = GlobalClass::instance()->getTex(1);

        //Elegir la textura del Quads: angulo cambia con el timer
        //glBindTexture(GL_TEXTURE_2D, texName[0]);

		glBindTexture(GL_TEXTURE_2D, tex0);

		glBegin(GL_QUADS);
        //Asignar la coordenada de textura 0,0 al vertice
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(minCoord, minCoord, 0);
        //Asignar la coordenada de textura 1,0 al vertice
        glTexCoord2f(1.0f, 0.0f); ///-
        glVertex3f(maxCoord, minCoord, 0);
        //Asignar la coordenada de textura 1,1 al vertice
        glTexCoord2f(1.0f,1.0f); //-
        //glTexCoord2f(1.0f,1.0f);
        //glTexCoord2f(2.0f,5.0f);
        glVertex3f(maxCoord, maxCoord, 0);
        //Asignar la coordenada de textura 0,1 al vertice
        glTexCoord2f(0.0f, 1.0f);
        //glTexCoord2f(0.0f, 5.0f);
        
        glVertex3f(minCoord, maxCoord, 0);
        glEnd();
        
    }
    glPopMatrix();
    
}
void Game::paintSphere(int x, int y, int z, int size, int texture){



	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);

//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); //GL_SPHERE_MAP
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    
    
    glPushMatrix();
    {

    	glTranslated(x,y,z);
    	glScalef(size, size, size);

    	glColor3f(1.0, 1.0, 1.0);
        //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    	glEnable(GL_TEXTURE_2D);

    	GLUquadricObj *qobj;

    	glBindTexture(GL_TEXTURE_2D, GlobalClass::instance()->getTex(texture));

    	glPushMatrix();
    	qobj = gluNewQuadric();
        //glTranslatef(x, y, z);
        gluQuadricDrawStyle(qobj, GLU_FILL); /* smooth shaded */
        //gluSphere(qobj, 20, 20, 20);
    	glutSolidSphere(18,20,20);
    	glPopMatrix();

    }

    glPopMatrix();
    
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_GEN_R);
    
}

void writeBigStringWide(GLdouble x, GLdouble y, string s, float size, int r, int g, int b){

	unsigned int i;

	glPushMatrix();
	glTranslatef(x, y, 0);

	glScaled( size, size, 0.2);

	glColor3ub(r, g, b);
	glLineWidth(50);
	for (i = 0; i < s.size(); i++){
		glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i]);
	}
	glLineWidth(1);
	glPopMatrix();
}

void Game::paintHUD(float x, float y, float w, float h){
	glViewport(x, y, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100, 100, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	writeBigStringWide(65, -93, "VEL", 0.075, 0, 255, 0);
	glBegin(GL_QUADS);
	{
		glColor3ub(0, 255, 0);
		glVertex2f(85, -95);
		glVertex2f(95, -95);

		glColor3ub(0 + jet.speed * 10, 255 - jet.speed * 10, 0);
		glVertex2f(95, -95 + jet.speed * 7);
		glVertex2f(85, -95 + jet.speed * 7);
	}
	glEnd();
	glColor3ub(255, 140, 0);
	glRectf(84, -96, 96, -96 + jet.speed * 7 + 2);
	writeBigStringWide(-93, 85, "VIDA", 0.075, 200, 0, 0);
    writeBigStringWide(5, 85, "PNTS: " + std::to_string(GlobalClass::instance()->getPoints()), 0.075, 200, 0, 0);
    writeBigStringWide(65, 85, formato(GlobalClass::instance()->getTimer()), 0.075, 200, 0, 0);
    if(gamePause){
        
        writeBigStringWide(-40, 0, "PAUSA", 0.2, 200, 0, 0);
    }
	glColor3ub(0, 255, 0);
	glRectf(-95, 82, 0 - 95 + jet.life*95/100, 95);
	glColor3ub(255, 0, 0);
	glRectf(-95, 82, 0, 95);
	glColor3ub(255, 140, 0);
	glRectf(-96, 81, 1, 96);
}

void Game::paintGame(float x, float y, float w, float h){
	glViewport(x, y, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, w/h, 0.01, 28000);
	camera.placeCamera(jet);
	glColor3ub(0,0,0);
	
	int imageDistance = 10000;

    //PAINT BACKGROUND
	paintBackGroundImage(0,0, imageDistance, 1, 0, 0, imageDistance * 2);
	paintBackGroundImage(0,0,-imageDistance, 1, 0, 0, imageDistance * 2);
	paintBackGroundImage(0,0, imageDistance, 0, 0, 1, imageDistance * 2);
	paintBackGroundImage(0,0,-imageDistance, 0, 0, 1, imageDistance * 2);
	paintBackGroundImage(0,0, imageDistance, 0, 1, 0, imageDistance * 2);
	paintBackGroundImage(0,0,-imageDistance, 0, 1, 0, imageDistance * 2);    

	paintBullets();

	glColor3f(1.0, 1.0, 1.0);


	for (int i = 0 ; i < PLANETS; i++) {
		paintSphere(planets[i].x,planets[i].y,planets[i].z, planets[i].size, planets[i].texture);
	}

	for (int i = 0 ; i < EVILS; i++) {
		if(evilscount[i]){
			paintModel(evils[i].texture, evils[i].x, evils[i].y, evils[i].z, evils[i].size);
			if(camera.first){
				evilsBody[i].testPaint();
			}
		}
	}

	for (int i = 0 ; i < HEALTHS; i++) {
		if (healthsTaken[i])
		{
			paintModel(healths[i].texture, healths[i].x, healths[i].y, healths[i].z, healths[i].size);
			if(camera.first){
				healthsBody[i].testPaint();
			}
		}
	}

	glColor3f(1.0, 1.0, 1.0);

	jet.paintJet();
}

void Game::display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	paintGame(0, 0, width, height);
	paintHUD(0, 0, width, height);
	glutSwapBuffers();
}

void Game::reshape(int w, int h){
	width = w;
	height = h;
}

void Game::keyboard(unsigned char key, int, int){
	Vector3d axis;
	axis = jet.up.cross(jet.forward);
	float angle = M_PI/16;
	camera.pitchMod = 0;
	camera.yawMod = 0;
	switch(key) {
		case 'w':
		rotateAxisVec(angle, axis, jet.forward);
		rotateAxisVec(angle, axis, jet.up);
		break;
		case 's':
		rotateAxisVec(-angle, axis, jet.forward);
		rotateAxisVec(-angle, axis, jet.up);
		break;
		case 'a':
		rotateUpZ(-angle, jet.forward, jet.up);
		break;
		case 'd':
		rotateUpZ(angle, jet.forward, jet.up);
		break;
		case 'q': 
		jet.jetBoost();
		break;
		case 'e': 
		jet.jetBrake();
		break;
		case 'y':
		camera.first = !camera.first;
		break;
		case 'i':
		camera.pitchMod = (M_PI / 2.3);
		break;
		case 'k':
		camera.pitchMod = -(M_PI / 2.3);
		break;
		case 'l':
		camera.yawMod = (M_PI / 2.3);
		break;
		case 'j':
		camera.yawMod = -(M_PI / 2.3);
		break;
		case 'm':
		shoot(0, true);
		break;
	}
	jet.up.normalize();
	jet.forward.normalize();
	axis = jet.up.cross(jet.forward);
}

float normalizeValues(int x, float a, float b){
	x = x + JOYSTICK_MAX_VALUE;
	float top = (x - NORMAL_MIN_VAL) * ( b - a ) * 1.0;
	float botom = NORMAL_MAX_VAL - NORMAL_MIN_VAL * 1.0;
	return a + top / botom * 1.0;
}

float normalizeValuesCamera(int x, float a, float b){
    //x = x + JOYSTICK_MAX_VALUE;
    float top = (x - JOYSTICK_MIN_VALUE) * ( b - a ) * 1.0;
    float botom = JOYSTICK_MAX_VALUE - JOYSTICK_MIN_VALUE * 1.0;
    return a + top / botom * 1.0;
}

void Game::EventLoop(int){
	SDL_Event sdlEvent;

	while( SDL_PollEvent( &sdlEvent ) ) {
		switch( sdlEvent.type ) {

			case SDL_CONTROLLERDEVICEADDED:
			cout << "AddController( sdlEvent.cdevice );" << endl;
			break;

			case SDL_CONTROLLERDEVICEREMOVED:
			cout << "RemoveController( sdlEvent.cdevice );" << endl;
			break;

			case SDL_CONTROLLERBUTTONDOWN:
			case SDL_CONTROLLERBUTTONUP:
			cout << "OnControllerButton( sdlEvent.cbutton );" << endl;
			break;

			case SDL_CONTROLLERAXISMOTION:
			cout << "OnControllerAxis( sdlEvent.caxis );" << endl;
			break;           
            //JOYSTICK
			case SDL_JOYAXISMOTION:
                // if(abs(sdlEvent.jaxis.value) > JOYSTICK_DEAD_ZONE){
                //  printf("Joystick %d axis %d value: %d\n",
                //      sdlEvent.jaxis.which,
                //      sdlEvent.jaxis.axis, sdlEvent.jaxis.value);
                // }
                //Motion on controller 0
			if( sdlEvent.jaxis.which == 0 ) {
                    //Z axis motion
				if( sdlEvent.jaxis.axis ==  LEFT_STICK_HORIZONTAL)  {
                        //Below of dead zone
                    
                    jet.rollMod = normalizeValuesCamera(sdlEvent.jaxis.value, -1, 1);
                    /*
					if( sdlEvent.jaxis.value < -JOYSTICK_DEAD_ZONE ) {
						//jet.rollMod = -1;
                        jet.rollMod = normalizeValues(sdlEvent.jaxis.value, 0, -1);
					}
                        //Above of dead zone
					else if( sdlEvent.jaxis.value > JOYSTICK_DEAD_ZONE ) {
						//jet.rollMod =  1;
                        jet.rollMod = normalizeValues(sdlEvent.jaxis.value, 0, 1);
                        
					}
                     */
                    
                    if (sdlEvent.jaxis.value < JOYSTICK_DEAD_ZONE && sdlEvent.jaxis.value > -JOYSTICK_DEAD_ZONE) {
                        jet.rollMod = 0;
                    }
					//else {
						//jet.rollMod = 0;
					//}
				}
                    //Y axis motion
				else if( sdlEvent.jaxis.axis == LEFT_STICK_VERTICAL ) {
                        //Left of dead zone
                    
                    jet.pitchMod = normalizeValuesCamera(sdlEvent.jaxis.value, 1, -1);

                    /*
					if( sdlEvent.jaxis.value < -JOYSTICK_DEAD_ZONE ) {
						//jet.pitchMod = 1;
                        //jet.pitchMod = normalizeValues(int x, float a, float b)
                        jet.pitchMod = normalizeValues(sdlEvent.jaxis.value, 0, 1);
                        
					}
                        //Right of dead zone
					else if( sdlEvent.jaxis.value > JOYSTICK_DEAD_ZONE ) {
						//jet.pitchMod =  -1;
                        jet.pitchMod = normalizeValues(sdlEvent.jaxis.value, 0, -1);
					}
					else {
						jet.pitchMod = 0;
					}
                    
                     */
                    if (sdlEvent.jaxis.value < JOYSTICK_DEAD_ZONE && sdlEvent.jaxis.value > -JOYSTICK_DEAD_ZONE) {
                        jet.pitchMod = 0;
                    }
                    
                    
                        //Yaw camera motion
				} else if( sdlEvent.jaxis.axis ==  RIGHT_STICK_HORIZONTAL)   {
                        //Below of dead zone
					if( sdlEvent.jaxis.value < -JOYSTICK_DEAD_ZONE ) {
						camera.yawMod = (M_PI / 2.3) * (sdlEvent.jaxis.value + JOYSTICK_DEAD_ZONE) / (JOYSTICK_MAX_VALUE - JOYSTICK_DEAD_ZONE);
					}
                        //Above of dead zone
					else if( sdlEvent.jaxis.value > JOYSTICK_DEAD_ZONE ) {
						camera.yawMod = (M_PI / 2.3) * (sdlEvent.jaxis.value - JOYSTICK_DEAD_ZONE) / (JOYSTICK_MAX_VALUE - JOYSTICK_DEAD_ZONE);
					}
					else {
						camera.yawMod = 0;
					}
				}
                    //Y axis motion
				else if( sdlEvent.jaxis.axis == RIGHT_STICK_VERTICAL ) {
                        //Left of dead zone
					if( sdlEvent.jaxis.value < -JOYSTICK_DEAD_ZONE ) {
						camera.pitchMod = (M_PI / 2.3) * (sdlEvent.jaxis.value + JOYSTICK_DEAD_ZONE) / (JOYSTICK_MAX_VALUE - JOYSTICK_DEAD_ZONE);
					}
                        //Right of dead zone
					else if( sdlEvent.jaxis.value > JOYSTICK_DEAD_ZONE ) {
						camera.pitchMod = (M_PI / 2.3) * (sdlEvent.jaxis.value - JOYSTICK_DEAD_ZONE) / (JOYSTICK_MAX_VALUE - JOYSTICK_DEAD_ZONE);
					}
					else {
						camera.pitchMod = 0;
					}
				} else if( sdlEvent.jaxis.axis == RT_AXIS ) {
                        //Full Trigger
                    if(!gamePause)
                        jet.setSpeed(normalizeValues(sdlEvent.jaxis.value, 6, 24));


					// printf("SPEED: %f\n", jet.getSpeed());
				}else if( sdlEvent.jaxis.axis == LT_AXIS ) {
                        //Full Trigger
                    if(!gamePause)
                        jet.setSpeed(normalizeValues(sdlEvent.jaxis.value, 6, 2));
                         // printf("SPEED: %f\n", jet.getSpeed());
				}
				else {
                        //SET SPEED TO NORMAL SPEED
					jet.setSpeed(6);

					if(abs(sdlEvent.jaxis.value) > JOYSTICK_DEAD_ZONE){
						printf("Joystick %d axis %d value: %d\n",
							sdlEvent.jaxis.which,
							sdlEvent.jaxis.axis, sdlEvent.jaxis.value);
					}
				}
			}
			break;
			case SDL_JOYHATMOTION:
			printf("Joystick %d hat %d value:",
				sdlEvent.jhat.which, sdlEvent.jhat.hat);
			if (sdlEvent.jhat.value == SDL_HAT_CENTERED)
				printf(" centered");
			if (sdlEvent.jhat.value & SDL_HAT_UP)
				printf(" up");
			if (sdlEvent.jhat.value & SDL_HAT_RIGHT)
				printf(" right");
			if (sdlEvent.jhat.value & SDL_HAT_DOWN)
				printf(" down");
			if (sdlEvent.jhat.value & SDL_HAT_LEFT)
				printf(" left");
			printf("\n");
			break;
			case SDL_JOYBALLMOTION:
			printf("Joystick %d ball %d delta: (%d,%d)\n",
				sdlEvent.jball.which,
				sdlEvent.jball.ball, sdlEvent.jball.xrel, sdlEvent.jball.yrel);
			break;
			case SDL_JOYBUTTONDOWN:

                // printf("Joystick %d button %d down\n",
                //  sdlEvent.jbutton.which, sdlEvent.jbutton.button);
			if( sdlEvent.jaxis.which == 0 ){  
				switch(sdlEvent.jbutton.button){
					case BUTTON_A:
                        if(!gamePause)
                            shoot(0, true);
					break;
					case BUTTON_B:
                        if(!gamePause)
                            jet.jetBrake();
                        break;
					case BUTTON_Y:
                        camera.first = !camera.first;
                        break;
                    case BUTTON_START:
                        gamePause = !gamePause;
                        break;
					default:
					printf("Joystick %d button %d down\n",
						sdlEvent.jbutton.which, sdlEvent.jbutton.button);
					break;
				}
			} else{
				printf("Joystick %d button %d down\n",
					sdlEvent.jbutton.which, sdlEvent.jbutton.button);
			}
			break;
                // case SDL_JOYBUTTONUP:
                // printf("Joystick %d button %d up\n",
                //  sdlEvent.jbutton.which, sdlEvent.jbutton.button);
                // break;
			case SDL_KEYDOWN:
			if ((sdlEvent.key.keysym.sym != SDLK_ESCAPE) && (sdlEvent.key.keysym.sym != SDLK_AC_BACK)) {
				break;
			}
                /* Fall through to signal quit */
        // YOUR OTHER EVENT HANDLING HERE

		}
	}
}

void paintModel(int tex, int x, int y, int z, int size){
	glPushMatrix();
	{
		glTranslatef(x, y, z);
		glScalef(size * 2, size  * 2, size  * 2);
		glmDraw(&gameModels[tex], GLM_COLOR | GLM_SMOOTH);
	}
	glPopMatrix();
}
