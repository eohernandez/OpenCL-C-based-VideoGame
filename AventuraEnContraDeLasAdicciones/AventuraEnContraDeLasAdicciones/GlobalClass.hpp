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

const int TEXTURE_COUNT=3;

class GlobalClass
{
    
    string fullPath;
    GLuint texName[TEXTURE_COUNT];

    static GlobalClass *s_instance;
    GlobalClass(string s = "")
    {
        fullPath = "";
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
    
    GLuint getTex(int n){
        return texName[n];
    }
    void initRendering();
    void loadTexture(Image* image,int k);
};


#endif /* GlobalClass_hpp */
