#ifndef MESH_HPP
#define MESH_HPP

#include <iostream>
#include <vector>
#include <Structs.hpp>

class Shaders;
class Model_Texture;

class Mesh
{
    public:
        std::vector<Vertex> _vertices;
        std::vector<unsigned int> _indices;
        std::vector<Texture> _textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        Mesh(const Mesh & src);
        ~Mesh();

        Mesh & operator=(const Mesh & src);
        void Draw(Shaders shader);
    private:
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
        void setupMesh();

        friend class Model_Texture;
};

#endif