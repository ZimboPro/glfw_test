#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 _position;
    glm::vec3 _normal;
    glm::vec2 _texCoords;
    glm::vec3 _tangent;
    glm::vec3 _bitangent;
};

struct Texture
{
    unsigned int _id;
    std::string _type;
    std::string _path;
};

struct Point
{
    float _x;
    float _y;
    float _z;
    float _degree;
}

#endif