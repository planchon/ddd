#ifndef MODEL
#define MODEL

#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.hpp"

using namespace std;

class Model {
public:
    Model(string path);
    void render(Shader& shader);
private:
    string path;
    vector<Mesh> meshes;
    vector<Texture> textures_loaded;
    string directory;

    void loadModel();
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
    Texture loadTextureFromFile(const char* textureName, string directory);
};

#endif