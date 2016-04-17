//
//  GlobalClass.cpp
//  AventuraEnContraDeLasAdicciones
//
//  Created by Enrique Hernandez on 4/13/16.
//  Copyright © 2016 Enrique. All rights reserved.
//

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include "glm/ImageLoader.hpp"


#include "GlobalClass.hpp"


//Makes the image into a texture, and returns the id of the texture
void GlobalClass::loadTexture(Image* image,int k)
{

    glBindTexture(GL_TEXTURE_2D, texName[k]); //Tell OpenGL which texture to edit
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    //Filtros de ampliacion y redución con cálculo mas cercano no es tan bueno pero es rápido
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    
    //Filtros de ampliacion y redución con cálculo lineal es mejo pero son más calculos
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image->pixels);               //The actual pixel data
}

void GlobalClass::initRendering()
{
    //Declaración del objeto Image
    Image* image;
    GLuint i=0;
    
    //int TEXTURE_COUNT = 2;
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    
    glEnable(GL_NORMALIZE);
    
    glEnable(GL_COLOR_MATERIAL);
    glGenTextures(TEXTURE_COUNT, texName); //Make room for our texture
    
    string s =  GlobalClass::instance()->get_path();
    
    
    char  ruta[300];
    sprintf(ruta,"%s%s", s.c_str() , "images/AventuraWallpaper.bmp");
    image = loadBMP(ruta);loadTexture(image,i++);
    
    sprintf(ruta,"%s%s", s.c_str() , "images/SpaceBackGround.bmp");
    image = loadBMP(ruta);loadTexture(image,i++);
    
    sprintf(ruta,"%s%s", s.c_str() , "images/Earth_texture.bmp");
    image = loadBMP(ruta);loadTexture(image,i++);
    
    sprintf(ruta,"%s%s", s.c_str() , "images/Moon.bmp");
    image = loadBMP(ruta);loadTexture(image,i++);

    sprintf(ruta,"%s%s", s.c_str() , "images/HUD.bmp");
    image = loadBMP(ruta);loadTexture(image,i++);
    
    delete image;
}

