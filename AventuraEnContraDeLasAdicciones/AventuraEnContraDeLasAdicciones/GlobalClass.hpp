//
//  GlobalClass.hpp
//  AventuraEnContraDeLasAdicciones
//
//  Created by Enrique Hernandez on 4/13/16.
//  Copyright © 2016 Enrique. All rights reserved.
//

#include "glm/ImageLoader.hpp"

#ifndef GlobalClass_hpp
#define GlobalClass_hpp


//const int TEXTURE_COUNT=1;


#include <string>

using namespace std;

const int TEXTURE_COUNT = 10;

class GlobalClass
{
    
    string fullPath;
    float timer;
    float totalGameTime;
    GLuint texName[TEXTURE_COUNT];
    int points;

    static GlobalClass *s_instance;
    GlobalClass(string s = "")
    {
        points = 0;
        fullPath = "";
        totalGameTime = 1800;
        timer = totalGameTime;
    }
    
public:
    string get_path()
    {
        return fullPath;
    }
    void set_path(string s)
    {
        fullPath = s;
    }
    static GlobalClass *instance()
    {
        if (!s_instance)
            s_instance = new GlobalClass;
        return s_instance;
    }
    
    void resetGameDefaults(){
        timer = totalGameTime;
        points = 0;
    }

    
    GLuint getTex(int n){
        return texName[n];
    }
    void setTimer(float t){
        timer = t;
    }
    int getPoints(){
        return points;
    }
    void updatePoints(int p){
        points += p;
    }
    
    float getTimer(){
        return timer;
    }
    void updateTimer(float t){
        timer -= t;
    }
    
    void initRendering();
    void loadTexture(Image* image,int k);
};


#endif /* GlobalClass_hpp */
