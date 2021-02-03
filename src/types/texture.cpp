#include "../../include/texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../include/stb/stb_image.h"

Texture::Texture(char* texturePath) {
    glGenTextures(1, &this->texture_id);
    glBindTexture(GL_TEXTURE_2D, this->texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    this->data = stbi_load(texturePath, &this->width, &this->height, &this->chanels, 0);

    if (this->data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "failed to load texture : " << texturePath << std::endl;
    }

    stbi_image_free(this->data);
}

Texture::Texture() {}

int Texture::get_id() {
    return this->texture_id;
}

std::string Texture::get_type() {
    return this->type;
}