#ifndef TEXTURE
#define TEXTURE

#include <iostream>
#include <string>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

class Texture {
public:
    Texture(char* texturePath);
    int get_id();
    std::string get_type();

private:
    int width, height, chanels;
    unsigned int texture_id;
    unsigned char* data;
    std::string type;
};

#endif