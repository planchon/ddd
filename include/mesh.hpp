#ifndef MESH
#define MESH

#include <vector>

#include "texture.hpp"
#include "math.hpp"
#include "shader.hpp"

using namespace std;

struct Vertex {
    vec3 position;
    vec3 normal;
    vec2 texCoord;
    vec3 tangent;
    vec3 biTangent;
};

class Mesh {
public:
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
    void render(Shader& shader);
private:
    unsigned int VAO, VBO, EBO;
    void setup();
};


#endif