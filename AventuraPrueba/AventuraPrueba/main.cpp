


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <windows.h>
#endif
#include <stdlib.h>
#include <string>
#include <fstream>
#include<sstream>
#include<stdio.h>
#include <iostream>
#include <math.h>
#include "glm.h"
#include "imageloader.h"
using namespace std;
GLMmodel model[1];
string fullPath = __FILE__;
GLuint texName[36];


void loadTexture(Image* image,int k)
{
    
    glBindTexture(GL_TEXTURE_2D, texName[k]); //Tell OpenGL which texture to edit
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    
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

void getParentPath(){
    for (int i = fullPath.length()-1; i>=0 && fullPath[i] != '\\'; i--) {
        fullPath.erase(i,1);
    }
}

//dibujar nave espacial
static void naveEspacial(){
    
    glmDraw(&model[0], GLM_COLOR);
    
}


float t=-1.0;
float delta=0.1;

void myTimer(int i) {
    delta = delta+ 5;
    glutPostRedisplay();
    glutTimerFunc(100,myTimer,1);
}

     
void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     
    glPushMatrix();
    glTranslatef(0, 1, -100);
    //glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
    glRotatef(180, 0, 1, 0);
    glRotatef(10, 1, 0, 0);
    //glScalef(1.2, 1.2, 0);
    glScalef(500, 500, 500);
    naveEspacial();
    glPopMatrix();
    
     
    glutSwapBuffers();
}

void init(){
    getParentPath();
    glEnable(GL_NORMALIZE);
    //string path = "/Users/enriqueohernandez/Dropbox/Escuela-/TEC/8 Semestre/Graficas Computacionales/Proyecto Final Git/OpenGL-Cpp-based-VideoGame/AventuraPrueba/AventuraPrueba/SpaceShip.obj";
    string path = "/Users/enriqueohernandez/Dropbox/Escuela-/TEC/8 Semestre/Graficas Computacionales/Proyecto Final Git/OpenGL-Cpp-based-VideoGame/AventuraPrueba/AventuraPrueba/starwarsShip.obj";
    //string path = fullPath + "SpaceShip.obj";
    model[0] = *glmReadOBJ(path.c_str());
    glmUnitize(&model[0]);
    glmVertexNormals(&model[0], 90.0, GL_TRUE);
    
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    
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
     switch (key){
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
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(33,myTimer,1);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return EXIT_SUCCESS;
}

#include <assert.h>
#include <fstream>

#include "imageloader.h"

using namespace std;

Image::Image(char* ps, int w, int h) : pixels(ps), width(w), height(h)
{
    
}

Image::~Image()
{
    delete[] pixels;
}

namespace
{
    //Converts a four-character array to an integer, using little-endian form
    int toInt(const char* bytes)
    {
        return (int)(((unsigned char)bytes[3] << 24) |
                     ((unsigned char)bytes[2] << 16) |
                     ((unsigned char)bytes[1] << 8) |
                     (unsigned char)bytes[0]);
    }
    
    //Converts a two-character array to a short, using little-endian form
    short toShort(const char* bytes)
    {
        return (short)(((unsigned char)bytes[1] << 8) |
                       (unsigned char)bytes[0]);
    }
    
    //Reads the next four bytes as an integer, using little-endian form
    int readInt(ifstream &input)
    {
        char buffer[4];
        input.read(buffer, 4);
        return toInt(buffer);
    }
    
    //Reads the next two bytes as a short, using little-endian form
    short readShort(ifstream &input)
    {
        char buffer[2];
        input.read(buffer, 2);
        return toShort(buffer);
    }
    
    //Just like auto_ptr, but for arrays
    template<class T>
    class auto_array
    {
    private:
        T* array;
        mutable bool isReleased;
    public:
        explicit auto_array(T* array_ = NULL) :
        array(array_), isReleased(false)
        {
        }
        
        auto_array(const auto_array<T> &aarray)
        {
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }
        
        ~auto_array()
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
        }
        
        T* get() const
        {
            return array;
        }
        
        T &operator*() const
        {
            return *array;
        }
        
        void operator=(const auto_array<T> &aarray)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }
        
        T* operator->() const
        {
            return array;
        }
        
        T* release()
        {
            isReleased = true;
            return array;
        }
        
        void reset(T* array_ = NULL)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = array_;
        }
        
        T* operator+(int i)
        {
            return array + i;
        }
        
        T &operator[](int i)
        {
            return array[i];
        }
    };
}

Image* loadBMP(const char* filename)
{
    ifstream input;
    input.open(filename, ifstream::binary);
    assert(!input.fail() || !"Could not find file");
    char buffer[2];
    input.read(buffer, 2);
    assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
    input.ignore(8);
    int dataOffset = readInt(input);
    
    //Read the header
    int headerSize = readInt(input);
    int width;
    int height;
    switch (headerSize)
    {
        case 40:
            //V3
            width = readInt(input);
            height = readInt(input);
            input.ignore(2);
            assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
            assert(readShort(input) == 0 || !"Image is compressed");
            break;
        case 12:
            //OS/2 V1
            width = readShort(input);
            height = readShort(input);
            input.ignore(2);
            assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
            break;
        case 64:
            //OS/2 V2
            assert(!"Can't load OS/2 V2 bitmaps");
            break;
        case 108:
            //Windows V4
            assert(!"Can't load Windows V4 bitmaps");
            break;
        case 124:
            //Windows V5
            assert(!"Can't load Windows V5 bitmaps");
            break;
        default:
            assert(!"Unknown bitmap format");
    }
    
    //Read the data
    int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
    int size = bytesPerRow * height;
    auto_array<char> pixels(new char[size]);
    input.seekg(dataOffset, ios_base::beg);
    input.read(pixels.get(), size);
    
    //Get the data into the right format
    auto_array<char> pixels2(new char[width * height * 3]);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                pixels2[3 * (width * y + x) + c] =
                pixels[bytesPerRow * y + 3 * x + (2 - c)];
            }
        }
    }
    
    input.close();
    return new Image(pixels2.release(), width, height);
}


