#include "Controls.h"

Controls::Controls(int w, int h){
    reshape(w, h);
    glutPostRedisplay();
	state = 3;
}

void Controls::timer(int v){

}

void Controls::display(){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    float minCoord = -50.0f;
    float maxCoord = 50.0f;
    glColor3f(255, 255, 255);
    
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
    
    glutSwapBuffers();
}

void Controls::reshape(int w, int h){

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-50, 50, -50, 50);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Controls::keyboard(unsigned char key, int, int){

}

void Controls::EventLoop(int){

    SDL_Event sdlEvent;
    
    while( SDL_PollEvent( &sdlEvent ) ) {
        switch( sdlEvent.type ) {
                
            case SDL_JOYBUTTONDOWN:
                // printf("Joystick %d button %d down\n",
                //  sdlEvent.jbutton.which, sdlEvent.jbutton.button);
                if( sdlEvent.jaxis.which == 0 ){
                    switch(sdlEvent.jbutton.button){
                            
                            
                        case BUTTON_B:
                            state = 0;
                            break;

                            
                        default:
                            break;
                    }
                } else{
                    printf("Joystick %d button %d down\n",
                           sdlEvent.jbutton.which, sdlEvent.jbutton.button);
                }
                break;
        }
    }
    

}