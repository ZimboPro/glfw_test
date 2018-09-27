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

struct Box
{
    float x1;
    float x2;
    float y1;
    float y2;
    float z1;
    float z2;
};

struct Rectangle
{
    float x1;
    float x2;
    float y1;
    float y2;
};

// struct BoundBox
// {
//     glm::vec3 right;
//     glm::vec3 left;
//     glm::vec3 front;
//     glm::vec3 back;
//     glm::vec3 top;
//     glm::vec3 bottom;
// }

#endif