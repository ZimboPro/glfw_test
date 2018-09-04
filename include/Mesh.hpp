#ifndef MESH_HPP
#define MESH_HPP

#include <iostream>
#include <vector>
#include <Structs.hpp>

class Shaders;

class Mesh
{
    public:
        std::vector<Vertex> _vertices;
        std::vector<unsigned int> _indices;
        std::vector<Texture> _textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        ~Mesh();
        void Draw(Shaders shader);
    private:
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
        void setupMesh();
};

#endif