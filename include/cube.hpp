#ifndef CUBE
#define CUBE

#include "math.hpp"

class Cube {
public:
    Cube(float size, glm::vec3 pos);
private:
    float[] vertices;
    glm::vec3 pos;
    float size;
}; 

#endif