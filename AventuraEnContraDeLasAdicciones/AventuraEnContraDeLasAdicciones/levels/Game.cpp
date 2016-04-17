#include "Game.h"

Game* game;

vector<bool> bodycount;

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

void timerShoot(int){
	game->shoot(0);
}

void Game::shoot(int){
	Bullet bu;
	bu.forward = jet.forward;
	Vector3d axis = jet.up.cross(jet.forward);
	bu.pos = Vector3d(jet.x + 2 * axis.x, jet.y + 2 * axis.y, jet.z + 2 * axis.z);
	bullets.push_back(bu);
	bu.pos = Vector3d(jet.x - 2 * axis.x, jet.y - 2 * axis.y, jet.z - 2 * axis.z);
	bullets.push_back(bu);
}

Game::Game(int w, int h){
	state = 1;
	glClearColor(.9, .9, .9, 1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	game = this;
	this->reshape(w,h);
	cout << "gamme" << endl;
   // initRendering();
	for (int i = 0; i < 5; ++i)
	{
		int x, y, z;
		x = rand() % 200 - 100;
		y = rand() % 200 - 100;
		z = rand() % 200 - 100;
		PhysicsBodyCube body(x, y, z, 10, 10, 10);
		baddie.push_back(body);
		bodycount.push_back(true);
	}
}

void Game::checkCollision(){
	for (int i = 0; i < bullets.size(); ++i)
	{
		if(!bullets[i].dead){
			for (int j = 0; j < baddie.size(); ++j)
			{
				if (bodycount[j] && bullets[i].body.collidesContinuos(baddie[j]))
				{
					bullets[i].dead = true;
					bodycount[j] = false;
				}
			}
		}
	}
}

void Game::timer(int v){
	checkCollision();
	moveBullets();
	jet.calcDir();
	jet.moveJet();
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
void Game::paintSphere(int x, int y, int z){

	glPushMatrix();
	{
		glTranslated(x,y,z);
		glScalef(5, 5, 5);

		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

		glColor3f(1.0, 1.0, 1.0);
		glEnable(GL_TEXTURE_2D);

		GLUquadricObj *qobj;

		glBindTexture(GL_TEXTURE_2D, GlobalClass::instance()->getTex(3));


		glPushMatrix();
		qobj = gluNewQuadric();
        //glTranslatef(x, y, z);
        gluQuadricDrawStyle(qobj, GLU_FILL); /* smooth shaded */
		gluSphere(qobj, 20, 20, 20);
		glutSolidSphere(20,20,20);
		glPopMatrix();


		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);

	}

	glPopMatrix();


}

void writeBigStringWide(GLdouble x, GLdouble y, string s, float size, int r, int g, int b){

    unsigned int i;
    
    glPushMatrix();
    glTranslatef(x, y, 0);
    
    glScaled( size, size * 3, 0.2);
    
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

    writeBigStringWide(-70, 70, "SPEED:", 0.075, 0, 255, 0);

	glColor3ub(255, 255, 255);
	
	float minCoord = -100.0f;
    float maxCoord = 100.0f;

	//Habilitar el uso de texturas
    glEnable(GL_TEXTURE_2D);
    
    GLuint tex0 = GlobalClass::instance()->getTex(4);
    
    //Elegir la textura del Quads: angulo cambia con el timer
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

void Game::paintGame(float x, float y, float w, float h){
	glViewport(x, y, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, w/h, 0.01, 15000);
	camera.placeCamera(jet);
	glColor3ub(0,0,0);

	int imageDistance = 5000;

    //PAINT BACKGROUND
	paintBackGroundImage(0,0, imageDistance, 1, 0, 0, imageDistance * 2);
	paintBackGroundImage(0,0,-imageDistance, 1, 0, 0, imageDistance * 2);
	paintBackGroundImage(0,0, imageDistance, 0, 0, 1, imageDistance * 2);
	paintBackGroundImage(0,0,-imageDistance, 0, 0, 1, imageDistance * 2);
	paintBackGroundImage(0,0, imageDistance, 0, 1, 0, imageDistance * 2);
	paintBackGroundImage(0,0,-imageDistance, 0, 1, 0, imageDistance * 2);    

	paintBullets();
	glColor3f(1.0, 1.0, 1.0);
	paintSphere(500,0,0);

    //glColor3ub(255,255,255);
	glColor3f(1.0, 1.0, 1.0);
	//paintBaddies();

	jet.paintJet();
}

void Game::display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	paintGame(0, height * 0.2, width, height * 0.8);
	paintHUD(0, 0, width, height * 0.2);
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
		shoot(0);
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
					if( sdlEvent.jaxis.value < -JOYSTICK_DEAD_ZONE ) {
						jet.rollMod = -1;
					}
                        //Above of dead zone
					else if( sdlEvent.jaxis.value > JOYSTICK_DEAD_ZONE ) {
						jet.rollMod =  1;
					}
					else {
						jet.rollMod = 0;
					}
				}
                    //Y axis motion
				else if( sdlEvent.jaxis.axis == LEFT_STICK_VERTICAL ) {
                        //Left of dead zone
					if( sdlEvent.jaxis.value < -JOYSTICK_DEAD_ZONE ) {
						jet.pitchMod = 1;
					}
                        //Right of dead zone
					else if( sdlEvent.jaxis.value > JOYSTICK_DEAD_ZONE ) {
						jet.pitchMod =  -1;
					}
					else {
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
					jet.setSpeed(normalizeValues(sdlEvent.jaxis.value, 6, 12));

					printf("SPEED: %f\n", jet.getSpeed());
				}else if( sdlEvent.jaxis.axis == LT_AXIS ) {
                        //Full Trigger

					jet.setSpeed(normalizeValues(sdlEvent.jaxis.value, 6, 2));
					printf("SPEED: %f\n", jet.getSpeed());
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
					shoot(0);
                            //jet.jetBoost();
					break;
					case BUTTON_B:
					jet.jetBrake();
					break;
					case BUTTON_Y:
					camera.first = !camera.first;
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
