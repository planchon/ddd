#ifndef SHADER
#define SHADER

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "math.hpp"

class Shader {
public:
    bool has_compiled;
    unsigned int program_id;

    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
    void use();

    void set(const std::string &name, bool value);
    void set(const std::string &name, int value);
    void set(const std::string &name, float value);
    void set(const std::string &name, glm::mat4 value);
};

#endif