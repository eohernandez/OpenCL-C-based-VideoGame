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

void DrawCube(GLfloat x, GLfloat y, GLfloat z, GLfloat length, bool fills = false, bool fill = false){
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

void paintGridAround(int count){

    // CARA 1

	for (int i = 0; i < count; ++i)
	{
		glPushMatrix();
		glTranslatef(i - count / 2, 0, count / 2);
		glScaled(.05, 100, .05);
		DrawCube(0, 0, 0, 4, true);
		glPopMatrix();
	}

	for (int i = 0; i < count; ++i)
	{
		glPushMatrix();
		glTranslatef(0, i - count / 2, count / 2);
		glScaled(100, .05, .05);
		DrawCube(0, 0, 0, 4, true);
		glPopMatrix();
	}

    // CARA 2

	for (int i = 0; i < count; ++i)
	{
		glPushMatrix();
		glTranslatef(i - count / 2, 0, -count / 2);
		glScaled(.05, 100, .05);
		DrawCube(0, 0, 0, 4, true);
		glPopMatrix();
	}

	for (int i = 0; i < count; ++i)
	{
		glPushMatrix();
		glTranslatef(0, i - count / 2, -count / 2);
		glScaled(100, .05, .05);
		DrawCube(0, 0, 0, 4, true);
		glPopMatrix();
	}

    // CARA 3

	for (int i = 0; i < count; ++i)
	{
		glPushMatrix();
		glTranslatef(i - count / 2, count / 2, 0);
		glScaled(.05, .05, 100);
		DrawCube(0, 0, 0, 4, true);
		glPopMatrix();
	}

	for (int i = 0; i < count; ++i)
	{
		glPushMatrix();
		glTranslatef(0, count / 2, i - count / 2);
		glScaled(100, .05, .05);
		DrawCube(0, 0, 0, 4, true);
		glPopMatrix();
	}

    // CARA 4

	for (int i = 0; i < count; ++i)
	{
		glPushMatrix();
		glTranslatef(i - count / 2, -count / 2, 0);
		glScaled(.05, .05, 100);
		DrawCube(0, 0, 0, 4, true);
		glPopMatrix();
	}

	for (int i = 0; i < count; ++i)
	{
		glPushMatrix();
		glTranslatef(0, -count / 2, i - count / 2);
		glScaled(100, .05, .05);
		DrawCube(0, 0, 0, 4, true);
		glPopMatrix();
	}

    // CARA 5

	for (int i = 0; i < count; ++i)
	{
		glPushMatrix();
		glTranslatef(count / 2, i - count / 2, 0);
		glScaled(.05, .05, 100);
		DrawCube(0, 0, 0, 4, true);
		glPopMatrix();
	}

	for (int i = 0; i < count; ++i)
	{
		glPushMatrix();
		glTranslatef(count / 2, 0, i - count / 2);
		glScaled(.05, 100, .05);
		DrawCube(0, 0, 0, 4, true);
		glPopMatrix();
	}

    // CARA 6

	for (int i = 0; i < count; ++i)
	{
		glPushMatrix();
		glTranslatef(-count / 2, i - count / 2, 0);
		glScaled(.05, .05, 100);
		DrawCube(0, 0, 0, 4, true);
		glPopMatrix();
	}

	for (int i = 0; i < count; ++i)
	{
		glPushMatrix();
		glTranslatef(-count / 2, 0, i - count / 2);
		glScaled(.05, 100, .05);
		DrawCube(0, 0, 0, 4, true);
		glPopMatrix();
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

void Game::paintBaddies(){
	for (int i = 0; i < baddie.size(); ++i)
	{
		if(bodycount[i]){
			DrawCube((baddie[i].maxv.x + baddie[i].minv.x) / 2, 
				(baddie[i].maxv.y + baddie[i].minv.y) / 2, 
				(baddie[i].maxv.z + baddie[i].minv.z) / 2,
				10, true);
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
	if (shooting)
	{
		glutTimerFunc(10, timerShoot, 0);
	}
}

Game::Game(int w, int h){
	state = 1;
	glClearColor(.9, .9, .9, 1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	game = this;
	this->reshape(w,h);
	cout << "gamme" << endl;
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
	camera.placeCamera(jet);
	glutPostRedisplay();
}

void Game::display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glColor3ub(0,0,0);

    //EJE X
	glPushMatrix();
	glScaled(100, .05, .05);
	DrawCube(0, 0, 0, 4, true);
	glPopMatrix();

    //EJE Y
	glPushMatrix();
	glScaled(.05, 100, .05);
	DrawCube(0, 0, 0, 4, true);
	glPopMatrix();

    //EJE Z
	glPushMatrix();
	glScaled(.05, .05, 100);
	DrawCube(0, 0, 0, 4, true);
	glPopMatrix();

	paintGridAround(400);

    //DrawCube(0, 0, 0, 4, true);

	paintBullets();

	glColor3ub(0,0,0);
	paintBaddies();

	jet.paintJet();

	glutSwapBuffers();
}

void Game::reshape(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, ((float)w)/h, 0.1, 10000);
	camera.placeCamera(jet);
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
		shooting = true;
		shoot(0);
		shooting = false;
		break;
	}
	jet.up.normalize();
	jet.forward.normalize();
	axis = jet.up.cross(jet.forward);
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

			case SDL_JOYAXISMOTION:
            // if(abs(sdlEvent.jaxis.value) > JOYSTICK_DEAD_ZONE){
            //  printf("Joystick %d axis %d value: %d\n",
            //      sdlEvent.jaxis.which,
            //      sdlEvent.jaxis.axis, sdlEvent.jaxis.value);
            // }
            //Motion on controller 0
			if( sdlEvent.jaxis.which == 0 ) {                        
                //Z axis motion
				if( sdlEvent.jaxis.axis ==  0)  {
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
				else if( sdlEvent.jaxis.axis == 1 ) {
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
				} else if( sdlEvent.jaxis.axis ==  2)   {
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
				else if( sdlEvent.jaxis.axis == 3 ) {
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
				} else if( sdlEvent.jaxis.axis == 4 ) {
                    //Full Trigger
					if( sdlEvent.jaxis.value == JOYSTICK_MAX_VALUE ) {
						shooting = true;
						shoot(0);
					} else {
						shooting = false;
					}
				}else {
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
					case 0:
					jet.jetBoost();
					break;
					case 1:
					jet.jetBrake();
					break;
					case 3:
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