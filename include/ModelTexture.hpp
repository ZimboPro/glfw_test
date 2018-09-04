#ifndef MODELTEXTURE_HPP
#define MODELTEXTURE_HPP

#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Structs.hpp>
#include <Mesh.hpp>
#include <iostream>

class Shaders;

class ModelTexture 
{
    public:
        /*  Functions   */
        ModelTexture();
        ModelTexture(char *path);
        ~ModelTexture();

        void loadModel(std::string path);
        bool IsLoaded() const;

    private:
        bool _isLoaded;
        std::vector<Mesh> _meshes;
        std::vector<Texture> _textureLoaded;
        std::string _directory;

        void Draw(const Shaders & shader);	
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
        unsigned int TextureFromFile(const char *path, const std::string &directory);

        friend class ModelSprite;
};

#endif