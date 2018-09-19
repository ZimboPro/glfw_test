#ifndef MODEL_TEXTURE_HPP
#define MODEL_TEXTURE_HPP

#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Structs.hpp>
#include <Mesh.hpp>
#include <iostream>

class Shaders;
//! Model_Texture class
/*!
    Stores the data of the models loaded
*/
class Model_Texture 
{
    public:
        /*  Functions   */
        /**
         * @brief Construct a new Model Texture object
         * 
         */
        Model_Texture();
        Model_Texture(const Model_Texture & src);
        Model_Texture & operator=(const Model_Texture & src);
        /**
         * @brief Construct a new Model Texture object
         * 
         * @param path the path to the model file
         */
        Model_Texture(char *path);
        ~Model_Texture();
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

        friend class Model_Sprite;
        friend class ModelGroup;
};

#endif