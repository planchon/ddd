#include "../../include/shader.hpp"

using namespace std; 

Shader::Shader(const char* shaderLocation, GLenum shader_type) {
    this->shader_id = glCreateShader(shader_type);

    // read the shader file
    ifstream source_code(shaderLocation);
    string contents((istreambuf_iterator<char>(source_code)), istreambuf_iterator<char>());
    this->shader_source_code = contents.c_str();
    this->compile();
}

void Shader::compile() {
    glShaderSource(this->shader_id, 1, &this->shader_source_code, NULL);
    glCompileShader(this->shader_id);

    glGetShaderiv(this->shader_id, GL_COMPILE_STATUS, &this->compile_sucess);
    glGetShaderInfoLog(this->shader_id, 2048, NULL, this->compile_log);

    this->has_compiled = false;

    if (!this->compile_sucess) {
        std::cout << "compile shader failed !\n" << this->compile_log << std::endl;
        this->has_compiled = false;
    } else {
        this->has_compiled = true;
    }

}

int Shader::get_id() {
    return this->shader_id;
}

ShaderProgram::ShaderProgram() {
    this->shader_program_id = glCreateProgram(); 
}

void ShaderProgram::addShader(Shader shader) {
    if (!shader.has_compiled) {
        shader.compile();
    }

    this->shaders.push_back(shader);
    glAttachShader(this->shader_program_id, shader.get_id());
}

void ShaderProgram::link() {
    glLinkProgram(this->shader_program_id);

    glGetProgramiv(this->shader_program_id, GL_LINK_STATUS, &this->link_sucess);
    glGetProgramInfoLog(this->shader_program_id, 2048, NULL, this->link_log);

    this->link_success = false;

    if (!this->link_sucess) {
        std::cout << "link shader program failed !\n" << this->link_log << std::endl;
    } else {
        this->link_success = true;
    }

    // delete the shader after the linkage process
    for (Shader shader : this->shaders) {
        glDeleteShader(shader.get_id());
    }
}

int ShaderProgram::get_id() {
    return this->shader_program_id;
}