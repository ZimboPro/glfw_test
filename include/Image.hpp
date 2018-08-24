#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <glm/glm.hpp>

class TextureImages;
class Shaders;
class Camera;

class Image
{
    public:
        Image(const float & x, const float & y, const float & width, const float & height, const glm::vec4 & color, unsigned int windowWidth, unsigned int windowHeight);
        Image(const float & x, const float & y, const float & width, const float & height, TextureImages * texture, unsigned int windowWidth, unsigned int windowHeight);
        ~Image();

        void Draw(Shaders & shader, Camera & camera);

    private:
        void Load();
        void LoadSquare();
        void Bind();
        void EnableVertex(int pointCount, int rowCount);
        void CalcPoints(const float & x, const float & y, const float & width, const float & height);

        TextureImages * _texture;
        glm::vec4 _color;
        float _xf;
        float _yf;
        float _x1;
        float _y1;
        float _indices[6];
        unsigned int _WinWidth;
        unsigned int _WinHeight;
        unsigned int _vao;
        unsigned int _vbo;
        unsigned int _ebo;
};

#endif