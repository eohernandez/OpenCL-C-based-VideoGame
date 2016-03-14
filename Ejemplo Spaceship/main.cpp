//
//  main.cpp
//  AventuraEnContraDeLasAdicciones
//
//  Created by Enrique Hernandez on 3/13/16.
//  Copyright © 2016 Enrique. All rights reserved.
//

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


/*
 * spaceship.c
 *
 *  Created on: Mar 30, 2014
 *      Author: kamath
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
//#include <GL/glut.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void initWindow(void);

float angle = 0.0;
int left, right;
int leftTime, rightTime;
int thrust, thrustTime;
int joyThrust = 0, joyLeft = 0, joyRight = 0;
float x = 20, y = 20, xv, yv, v;
int shield = 0, joyShield = 0, cursor = 1;
int lastTime;
int paused = 0;
int resuming = 1;
int originalWindow = 0, currentWindow;

typedef struct {
    int inuse;
    
    float x;
    float y;
    
    float v;
    float xv;
    float yv;
    
    int expire;
} Bullet;

#define MAX_BULLETS 10

Bullet bullet[MAX_BULLETS];

int allocBullet(void)
{
    int i;
    
    for (i=0; i<MAX_BULLETS; i++) {
        if (!bullet[i].inuse) {
            return i;
        }
    }
    return -1;
}






void initBullet(int i, int time)
{
    float c = cos(angle*M_PI/180.0);
    float s = sin(angle*M_PI/180.0);
    
    bullet[i].inuse = 1;
    bullet[i].x = x + 2 * c;
    bullet[i].y = y + 2 * s;
    bullet[i].v = 0.025;
    bullet[i].xv = xv + c * bullet[i].v;
    bullet[i].yv = yv + s * bullet[i].v;
    bullet[i].expire = time + 1000;
}


void advanceBullets(int delta, int time)
{
    int i;
    
    for (i=0; i<MAX_BULLETS; i++) {
        if (bullet[i].inuse) {
            float x, y;
            
            if (time > bullet[i].expire) {
                bullet[i].inuse = 0;
                continue;
            }
            x = bullet[i].x + bullet[i].xv * delta;
            y = bullet[i].y + bullet[i].yv * delta;
            x = x / 40.0;
            bullet[i].x = (x - floor(x))*40.0;
            y = y / 40.0;
            bullet[i].y = (y - floor(y))*40.0;
        }
    }
}


void shotBullet(void)
{
    int entry;
    
    entry = allocBullet();
    if (entry >= 0) {
        initBullet(entry, glutGet(GLUT_ELAPSED_TIME));
    }
}


void drawBullets(void)
{
    int i;
    
    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 1.0);
    for (i=0; i<MAX_BULLETS; i++) {
        if (bullet[i].inuse) {
            glVertex2f(bullet[i].x, bullet[i].y);
        }
    }
    glEnd();
}
void drawShip(float angle)
{
    float rad;
    
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    if (thrust)
    {
        
        //-------------flame----------------
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex2f(-7.0,1.5);
        glVertex2f(-6.0,1.5);
        glEnd();
        
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex2f(-6.0,1.0);
        glVertex2f(-5.0,1.0);
        glEnd();
        
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex2f(-7.0,0.5);
        glVertex2f(-6.0,0.5);
        glEnd();
        
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex2f(-6.0,0.0);
        glVertex2f(-5.0,0.0);
        glEnd();
        
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex2f(-7.0,-0.5);
        glVertex2f(-6.0,-0.5);
        glEnd();
        
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex2f(-6.0,-1.0);
        glVertex2f(-5.0,-1.0);
        glEnd();
        
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex2f(-7.0,-1.5);
        glVertex2f(-6.0,-1.5);
        glEnd();
        
    }
    
    //--------------------center fornt-----------------
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(3.0, 0.0);
    glVertex2f(-2.5, -2.5);
    glVertex2f(1.0, 0.0);
    glVertex2f(-2.5, 2.5);
    glVertex2f(3.0, 0.0);
    glEnd();
    
    
    
    //---------------------center-----------
    
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(-2.5, 2.5);
    glVertex2f(-3.0, 2.0);
    glVertex2f(-3.0, -2.0);
    glVertex2f(-2.5, -2.5);
    glVertex2f(1.0,0.0);
    glVertex2f(-2.5,2.5);
    glEnd();
    
    //-----end--
    glColor3f(1.0, 1.0, 0.5);
    glBegin(GL_POLYGON);
    glVertex2f(-3.0,2.0);
    glVertex2f(-3.0,-2.0);
    glVertex2f(-4.5,-3.5);
    glVertex2f(-5.5,-2.5);
    glVertex2f(-4.5,-1.5);
    glVertex2f(-4.5,1.5);
    glVertex2f(-5.5,2.5);
    glVertex2f(-4.5,3.5);
    glVertex2f(-3.0,2.0);
    glEnd();
    
    //----------- flaps ----------
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-1.5,2.0);
    glVertex2f(-0.8,2.6);
    glVertex2f(3.0,0.0);
    glVertex2f(-1.5,2.0);
    glEnd();
    
    //------------------flaps------
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-1.5,-2.0);
    glVertex2f(-0.8,-2.6);
    glVertex2f(3.0,0.0);
    glVertex2f(-1.5,-2.0);
    glEnd();
    
    //--------------front rectangle------------
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(1.25,0.4);
    glVertex2f(1.75,0.4);
    glVertex2f(1.25,-0.4);
    glVertex2f(1.75,-0.4);
    glVertex2f(1.75,0.4);
    glEnd();
    
    //--------------------stars---------------
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2f(1.5,0.0);
    glEnd();
    
    //-points-
    if (shield)
    {
        glColor3f(0.1, 0.1, 1.0);
        glBegin(GL_LINE_LOOP);
        for (rad=0.0; rad<30.0; rad += 1.0) {
            glVertex2f(3.2 * cos(2*rad/M_PI)+0.2, 3.0 * sin(2*rad/M_PI));
        }
        glEnd();
    }
    glPopMatrix();
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    drawShip(angle);
    drawBullets();
    
    
    
    glutSwapBuffers();
}


void idle(void)
{
    int time, delta;
    
    time = glutGet(GLUT_ELAPSED_TIME);
    if (resuming) {
        lastTime = time;
        resuming = 0;
    }
    if (left) {
        delta = time - leftTime;
        angle = angle + delta * 0.4;
        leftTime = time;
    }
    if (right) {
        delta = time - rightTime;
        angle = angle - delta * 0.4;
        rightTime = time;
    }
    if (thrust) {
        delta = time - thrustTime;
        v = delta * 0.00004;
        xv = xv + cos(angle*M_PI/180.0) * v;
        yv = yv + sin(angle*M_PI/180.0) * v;
        thrustTime = time;
    }
    delta = time - lastTime;
    x = x + xv * delta;
    y = y + yv * delta;
    x = x / 40.0;
    x = (x - floor(x))*40.0;
    y = y / 40.0;
    y = (y - floor(y))*40.0;
    lastTime = time;
    advanceBullets(delta, time);
    glutPostWindowRedisplay(currentWindow);
}


void visible(int vis)
{
    if (vis == GLUT_VISIBLE) {
        if (!paused) {
            glutIdleFunc(idle);
        }
    } else {
        glutIdleFunc(NULL);
    }
}


/* ARGSUSED1 */
void key(unsigned char key, int px, int py)
{
    switch (key) {
        case 27:
            exit(0);
            break;
        case 'A':
        case 'a':
            thrust = 1;
            thrustTime = glutGet(GLUT_ELAPSED_TIME);
            break;
        case 'S':
        case 's':
            shield = 1;
            break;
        case 'C':
        case 'c':
            cursor = !cursor;
            glutSetCursor(
                          cursor ? GLUT_CURSOR_INHERIT : GLUT_CURSOR_NONE);
            break;
        case 'z':
        case 'Z':
            x = 20;
            y = 20;
            xv = 0;
            yv = 0;
            break;
            
        case 'P':
        case 'p':
            paused = !paused;
            if (paused) {
                glutIdleFunc(NULL);
            } else {
                glutIdleFunc(idle);
                resuming = 1;
            }
            break;
        case 'Q':
        case 'q':
        case ' ':
            shotBullet();
            break;
    }
}


/* ARGSUSED1 */
void keyup(unsigned char key, int x, int y)
{
    switch (key) {
        case 'A':
        case 'a':
            thrust = 0;
            break;
        case 'S':
        case 's':
            shield = 0;
            break;
    }
}


/* ARGSUSED1 */
void special(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_F1:
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
            glEnable(GL_LINE_SMOOTH);
            glEnable(GL_POINT_SMOOTH);
            break;
        case GLUT_KEY_F2:
            glDisable(GL_BLEND);
            glDisable(GL_LINE_SMOOTH);
            glDisable(GL_POINT_SMOOTH);
            break;
        case GLUT_KEY_UP:
            thrust = 1;
            thrustTime = glutGet(GLUT_ELAPSED_TIME);
            break;
        case GLUT_KEY_LEFT:
            left = 1;
            leftTime = glutGet(GLUT_ELAPSED_TIME);
            break;
        case GLUT_KEY_RIGHT:
            right = 1;
            rightTime = glutGet(GLUT_ELAPSED_TIME);
            break;
    }
}


/* ARGSUSED1 */
void specialup(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_UP:
            thrust = 0;
            break;
        case GLUT_KEY_LEFT:
            left = 0;
            break;
        case GLUT_KEY_RIGHT:
            right = 0;
            break;
    }
}


/* ARGSUSED3 */
void joystick(unsigned int buttons, int x, int y, int z)
{
    if (buttons & 0x1) {
        thrust = 1;
        thrustTime = glutGet(GLUT_ELAPSED_TIME);
        joyThrust = 1;
    } else {
        if (joyThrust) {
            thrust = 0;
            joyThrust = 0;
        }
    }
    if (buttons & 0x2) {
        shotBullet();
    }
    if (buttons & 0x4) {
        shield = 1;
        joyShield = 1;
    } else {
        if (joyShield) {
            shield = 0;
            joyShield = 0;
        }
    }
    if (x < -300) {
        left = 1;
        leftTime = glutGet(GLUT_ELAPSED_TIME);
        joyLeft = 1;
    } else {
        /* joyLeft helps avoid "joystick in neutral"
         from continually stopping rotation. */
        if (joyLeft) {
            left = 0;
            joyLeft = 0;
        }
    }
    if (x > 300) {
        right = 1;
        rightTime = glutGet(GLUT_ELAPSED_TIME);
        joyRight = 1;
    } else {
        /* joyRight helps avoid "joystick in neutral"
         from continually stopping rotation. */
        if (joyRight) {
            right = 0;
            joyRight = 0;
        }
    }
}








void initWindow(void)
{
    glutIgnoreKeyRepeat(1);
    glutDisplayFunc(display);
    glutVisibilityFunc(visible);
    glutKeyboardFunc(key);
    glutKeyboardUpFunc(keyup);
    glutSpecialFunc(special);
    glutSpecialUpFunc(specialup);
    glutJoystickFunc(joystick, 100);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 40, 0, 40, 0, 40);
    glMatrixMode(GL_MODELVIEW);
    glPointSize(3.0);
    
    currentWindow = glutGetWindow();
}


int  main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    
    if (argc > 1 && !strcmp(argv[1], "-fullscreen")) {
        glutGameModeString("640x480:16@60");
        glutEnterGameMode();
    } else {
        originalWindow = glutCreateWindow("SPACE SHIP");
    }
    
    initWindow();
    
    glutMainLoop();
    return 0;             /* ANSI C requires main to return int. */
}

/*

#include <stdlib.h>
float t=-1.0;
float delta=0.1;
int aguila[][2]=
{
    {385,616},{292,585},{370,355},
    {288,597},{370,355},{223,563},
    {209,584},{370,355},{178,494},
    {140,522},{370,355},{168,461},
    {131,480},{370,355},{145,439},
    {117,449},{370,355},{164,399},
    {164,399},{466,334},{458,293},
    {164,399},{458,293},{195,352},
    {165,360},{458,293},{274,291},
    {254,291},{459,293},{422,267},
    {254,291},{421,267},{451,235},
    {254,291},{451,235},{378,196},
    {378,196},{451,235},{488,186},
    {451,235},{552,218},{488,186},
    {451,235},{491,265},{552,218},
    {385,603},{436,610},{370,356},
    {432,594},{466,572},{370,356},
    {460,559},{483,531},{370,356},
    {480,527},{501,498},{370,356},
    {501,498},{438,359},{370,356},
    {469,428},{516,364},{438,359},
    {370,355},{571,367},{466,334},
    {516,364},{652,392},{571,367},
    {466,334},{652,392},{612,353},
    {466,334},{612,353},{534,327},
    {466,334},{534,327},{573,296},
    {466,334},{573,296},{458,293},
    {458,293},{573,296},{491,265},
    {491,265},{573,296},{552,218},
    {573,296},{598,219},{552,218},
    {573,296},{668,259},{598,219},
    {573,296},{646,298},{668,259},
    {646,298},{683,311},{668,259},
    {666,354},{683,311},{646,298},
    {421,267},{491,265},{451,235},
    {421,267},{458,293},{491,265},
    {443,266},{452,273},{470,265},
    {443,266},{470,265},{451,254},
};
int color[][3]=
{
    {138,145,155},
    {176,186,196},
    {202,214,226},
    {223,231,239},
    {214,224,234},
    {214,224,234},
    {138,145,155},
    {176,186,196},
    {202,214,226},
    {223,231,239},
    {214,224,234},
    {214,224,234},
    {223,231,239},
    {176,186,196},
    {202,214,226},
    {123,130,138},
    {120,130,148},
    {138,145,155},
    {123,130,138},
    {115,119,120},
    {79,79,79},
    {65,65,68},
    {65,65,68},
    {225,185,116},
    {75,50,53},
    {75,50,53},
    {191,175,100},
    {225,185,116},
    {219,191,53},
    {194,178,90},
    {191,175,100},
    {225,185,116},
    {219,191,53},
    {191,175,100},
    {219,191,53},
    {219,191,53},
    {51,255,254},
    {51,255,254},
};

int eagle;

void myTimer(int i) {
    delta = delta+ 5;
    glutPostRedisplay();
    glutTimerFunc(100,myTimer,1);
}

void crearLista(){
    //creamos la topologia
 
 
 */
    /*
     for(int iK = 0; iK <= 114; iK++){
     indicesAguila[iK] = iK;
     }
     
     
     //Habilitar el arreglo de vértices
     glEnableClientState(GL_VERTEX_ARRAY);
     glVertexPointer(3, GL_FLOAT, 0, aguila);
     
     //Habilitar el arreglo de colores
     glEnableClientState(GL_COLOR_ARRAY);
     glColorPointer(3, GL_FLOAT,0, colores);
      */
    
    /*
    
    eagle = glGenLists(1);
    glNewList(eagle, GL_COMPILE);
    
    glBegin(GL_TRIANGLES);
    for (int k=0; k<=114;k++)
    {
        glColor3ub(color[k/3][0],color[k/3][1],color[k/3][2]);
        glVertex2i(aguila[k][0], 800-aguila[k][1]);
    }
    glEnd();
    
    
    
    glEndList();
    
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    //glPointSize(50);
    
    glPushMatrix();
    glTranslated(delta, 0, 0);
    
    
    glPushMatrix();
    //glTranslated(400, 400, 0);
    glScalef(1.2, 1.2, 0);
    glCallList(eagle);
    glPopMatrix();
    
    
    glPopMatrix();
    
    glutSwapBuffers();//ya tiene integrado el glFlush
}


void reshape (int a,int alto)
{
    glViewport(0, 0, a, alto);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar)
    glFrustum(-1000, 1000, -1000, 1000, 10, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ, GLdouble centerX, GLdouble centerY, GLdouble centerZ, GLdouble upX, GLdouble upY, GLdouble upZ)
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
}

void keyboard(unsigned char key, int mouseX, int mouseY)
{
    switch (key)
    {
        case 'o':
        case 'O':
            //opcion = 1;
            reshape(600,600);
            break;
        case 'p':
        case 'P':
            //opcion = 2;
            reshape(600,600);
            break;
        case 'r':
        case 'R':
            //  init();
            break;
        case 27: exit(0); break;
        default:
            break;
    }
    
    
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(1000,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Poligonos");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    crearLista();
    glutTimerFunc(33,myTimer,1);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return EXIT_SUCCESS;
}
     
     */
