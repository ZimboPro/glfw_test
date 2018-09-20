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
        /**
         * @brief A vector storing all the vertices
         * 
         */
        std::vector<Vertex> _vertices;
        /**
         * @brief A vector storing all the indices for the vertices
         * 
         */
        std::vector<unsigned int> _indices;
        /**
         * @brief A vector storing all the texture data for the vertices
         * 
         */
        std::vector<Texture> _textures;
        /**
         * @brief Construct a new Mesh object
         * 
         * @param vertices 
         * @param indices 
         * @param textures 
         */
        Mesh(std::vector<Vertex> & vertices, std::vector<unsigned int> & indices, std::vector<Texture> & textures);
        /**
         * @brief Construct a new Mesh object
         * 
         * @param src The instance to copy
         */
        Mesh(const Mesh & src);
        ~Mesh();
        /**
         * @brief Assign the data in the right instance to the left
         * 
         * @param src 
         * @return Mesh& 
         */
        Mesh & operator=(const Mesh & src);
        /**
         * @brief Draw the mesh
         * 
         * @param shader 
         */
        void Draw(Shaders & shader);
    private:
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
        void setupMesh();

        friend class Model_Texture;
};

#endif