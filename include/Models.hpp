#ifndef MODELS_HPP
#define MODELS_HPP

#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Structs.hpp>
#include <Mesh.hpp>

class Shaders;

class Model 
{
    public:
        /*  Functions   */
        Model(char *path, const glm::vec3 & postion = glm::vec3(0.0f), const glm::vec3 & scale = glm::vec3(1.0f) ,bool gama = false);
        void Draw(Shaders & shader);	
        void Translate(const glm::vec3 & translate);
        void DrawAndSet(Shaders & shader, const std::string & name);
        void Position(const glm::vec3 & position);
        void Scale(const glm::vec3 & scale);
        void Reset();
        void NewPostionAndScale(const glm::vec3 & position, const glm::vec3 & scale);

    private:
        glm::mat4 _transformationMatrix;
        std::vector<Mesh> _meshes;
        std::vector<Texture> _textureLoaded;
        std::string _directory;
        bool _gammaCorrection;

        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
        unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
};

#endif