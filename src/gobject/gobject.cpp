#include "../../include/gobject.hpp"

GObject::GObject(float* vertices, glm::vec3 position) {
    this->position = position;
    this->vertices = vertices;

    
}