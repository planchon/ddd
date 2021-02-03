#include "mesh.hpp"

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    this->setup();
}

void Mesh::setup() {
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // memory setup
    // FLOAT FLOAT FLOAT | FLOAT FLOAT FLOAT | FLOAT FLOAT | FLOAT FLOAT FLOAT | FLOAT FLOAT FLOAT
    //    vertex              normal            texture          tangent             bitangent

    //vertex data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);

    // normal data
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, normal));

    // texture data
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, texCoord));

    // tangent data
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3,3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, tangent));

    // bi tangent data
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4,3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, biTangent));

    glBindVertexArray(0);
}

void Mesh::render(Shader& shader) {
    unsigned int n_diffuse  = 1;
    unsigned int n_specular = 1;
    unsigned int n_normal   = 1;
    unsigned int n_height   = 1;

    for (int i = 0; i < this->textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        string number;
        string name = this->textures[i].get_type();

        if (name == "texture_diffuse") {
            number = std::to_string(n_diffuse++);
        } else if (name == "texture_specular") {
            number = std::to_string(n_specular++);
        } else if (name == "texture_normal") {
            number = std::to_string(n_normal++);
        } else if (name == "texture_height") {
            number = std::to_string(n_height++);
        }

        shader.set((name + number).c_str(), i);
    }

    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // reset
    glActiveTexture(GL_TEXTURE0);
}