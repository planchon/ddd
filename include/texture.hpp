#ifndef TEXTURE
#define TEXTURE

#include <iostream>
#include <string>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "stb/stb_image.h"

using namespace std;

class Texture {
public:
    string path;
    unsigned int texture_id;
    string type;
    int width, height, chanels;
    unsigned char* data;

    Texture();
    Texture(char* texturePath);
    int get_id();
    string get_type();    
};



#endif