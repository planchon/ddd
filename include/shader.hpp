#ifndef SHADER
#define SHADER

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>

class Shader {
public:
    bool has_compiled;

    Shader(const char* shaderLocation, GLenum shader_type);
    void compile();
    int get_id();

private:
    const char* shader_source_code;
    unsigned int shader_id;
    int compile_sucess;
    char compile_log[2048];
};

class ShaderProgram {
public:
    bool link_success;

    ShaderProgram();
    void addShader(Shader shader);
    void link();

private:
    unsigned int shader_program_id;
    std::vector<Shader> shaders;

    int link_sucess;
    char link_log[2048];
};

#endif