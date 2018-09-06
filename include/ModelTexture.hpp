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
//! ModelTexture class
/*!
    Stores the data of the models loaded
*/
class ModelTexture 
{
    public:
        /*  Functions   */
        /**
         * @brief Construct a new Model Texture object
         * 
         */
        ModelTexture();
        /**
         * @brief Construct a new Model Texture object
         * 
         * @param path the path to the model file
         */
        ModelTexture(char *path);
        ~ModelTexture();
        /**
         * @brief Loads the model
         * 
         * @param path the path to the model file
         */
        void loadModel(std::string path);
        /**
         * @brief Returns true if a model has been loaded
         * 
         * @return true 
         * @return false 
         */
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
        friend class ModelGroup;
};

#endif