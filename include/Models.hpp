#ifndef MODELS_HPP
#define MODELS_HPP

#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Structs.hpp>
#include <Mesh.hpp>
#include <iostream>

class Shaders;

class Model 
{
    public:
        /*  Functions   */
        Model(char *path, const glm::vec3 & postion = glm::vec3(0.0f), const glm::vec3 & scale = glm::vec3(1.0f) ,bool gama = false);
        void Draw(const Shaders & shader);	
        void DrawAndSet(const Shaders & shader, const std::string & name);
        void Position(const glm::vec3 & position);
        void Scale(const glm::vec3 & scale);
        void Scale(const float & scale);
        void Reset();
        void Rotate(const float & degrees);
        void Rotate(const float & degrees, const glm::vec3 & axis);
        void DrawAt(const Shaders & shader, const float & x, const float & y, const float & z = 0, const float & degree = 0);
        void NewPostionAndScale(const glm::vec3 & position, const glm::vec3 & scale, const float & degrees = 0);
        void NewPostionAndScale(const glm::vec3 & position, const float & scale, const float & degrees = 0);

    private:
        glm::mat4 _transformationMatrix;
        std::vector<Mesh> _meshes;
        std::vector<Texture> _textureLoaded;
        std::string _directory;
        bool _gammaCorrection;
        glm::vec3 _scale;

        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
        unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
};

#endif