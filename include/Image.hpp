#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <glm/glm.hpp>

class TextureImages;

class Image
{
    public:
        Image(const float & x, const float & y, const float & width, const float & height, const glm::vec4 & color);
        Image(const float & x, const float & y, const float & width, const float & height, const TextureImages * texture);
        ~Image();

        void Draw();
        void Point(const float & x, const float & y);

    private:
        TextureImages * _texture;
        glm::vec4 _color;
        float _x;
        float _y;
        float _width;
        float _height;
};

#endif