#ifndef GOBJECT
#define GOBJECT

#include "math.hpp"

class GObject {
public:
    GObject(float* vertices, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
    void tick();
    void render();

private:
    glm::vec3 position;
    float* vertices;
};

#endif