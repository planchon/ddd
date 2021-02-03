#include "../../include/shader.hpp"

using namespace std; 

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
    std::string vertexShaderCode;
    std::string fragmentShaderCode;
    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;
    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    // on ouvre le code du shader et on le place dans une string
    try {
        vertexShaderFile.open(vertexShaderPath);
        fragmentShaderFile.open(fragmentShaderPath);    

        vertexShaderCode = string((std::istreambuf_iterator<char>(vertexShaderFile)), std::istreambuf_iterator<char>());
        fragmentShaderCode = string((std::istreambuf_iterator<char>(fragmentShaderFile)), std::istreambuf_iterator<char>());
    } catch (std::ifstream::failure e) {
        std::cout << "error reading shader source code : " << e.what() << std::endl;
    }

    // on creer le shader et on le compile
    unsigned int vertexID, fragmentID;
    int success;
    char logInfo[2048];

    const char* codeBuffer = vertexShaderCode.c_str();

    vertexID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexID, 1, &codeBuffer, nullptr);
    glCompileShader(vertexID);

    // on regarde si le shader a bien été compilé
    glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexID, 2048, nullptr, logInfo);
        std::cout << "error compiling " << vertexShaderPath << " : \n" << logInfo << std::endl;
    }

    // on compile le fragment shader
    codeBuffer = fragmentShaderCode.c_str();

    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentID, 1, &codeBuffer, nullptr);
    glCompileShader(fragmentID);

    // on regarde si le shader a bien été compilé
    glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentID, 2048, nullptr, logInfo);
        std::cout << "error compiling " << fragmentShaderPath << " : \n" << logInfo << std::endl;
    }

    this->program_id = glCreateProgram();
    glAttachShader(this->program_id, vertexID);
    glAttachShader(this->program_id, fragmentID);
    glLinkProgram(this->program_id);

    glGetProgramiv(this->program_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->program_id, 2048, nullptr, logInfo);
        std::cout << "error linking shaders (" << vertexShaderPath << ", " << fragmentShaderPath << ") : \n" << logInfo << std::endl;
    }

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
}

void Shader::use() {
    glUseProgram(this->program_id);
}

void Shader::set(const std::string &name, bool value) {
    glUniform1i(glGetUniformLocation(this->program_id, name.c_str()), (int) value);
}

void Shader::set(const std::string &name, int value) {
    glUniform1i(glGetUniformLocation(this->program_id, name.c_str()), value);
}

void Shader::set(const std::string &name, float value) {
    glUniform1f(glGetUniformLocation(this->program_id, name.c_str()), value);
}

void Shader::set(const std::string &name, glm::mat4 value) {
    int id = glGetUniformLocation(this->program_id, name.c_str());
    glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(value));
}