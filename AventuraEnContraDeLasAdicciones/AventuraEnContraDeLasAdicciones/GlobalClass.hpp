//
//  GlobalClass.hpp
//  AventuraEnContraDeLasAdicciones
//
//  Created by Enrique Hernandez on 4/13/16.
//  Copyright © 2016 Enrique. All rights reserved.
//

#ifndef GlobalClass_hpp
#define GlobalClass_hpp

#include <stdio.h>

#include <string>
using namespace std;
class GlobalClass
{
    string fullPath;
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
};




#endif /* GlobalClass_hpp */
