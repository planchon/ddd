#include "../../include/mesh.hpp"

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
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), this->vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), &this->indices[0], GL_STATIC_DRAW);

    // memory setup
    // FLOAT FLOAT FLOAT | FLOAT FLOAT FLOAT | FLOAT FLOAT | FLOAT FLOAT FLOAT | FLOAT FLOAT FLOAT
    //    vertex              normal            texture          tangent             bitangent

    //vertex data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);

    // normal data
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, normal));

    // texture data
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, texCoord));

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

        if (name == "diffuse") {
            number = std::to_string(n_diffuse++);
        } else if (name == "specular") {
            number = std::to_string(n_specular++);
        } else if (name == "normal") {
            number = std::to_string(n_normal++);
        } else if (name == "height") {
            number = std::to_string(n_height++);
        }

        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader.program_id, (name + number).c_str()), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textures[i].texture_id);
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // reset
    glActiveTexture(GL_TEXTURE0);
}