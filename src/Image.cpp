#include <Image.hpp>

Image::Image(const float & x, const float & y, const float & width, const float & height, const glm::vec4 & color)
{
    this->_x = x;
    this->_y = y;
    this->_width = width;
    this->_height = height;
    this->_color = color;
    this->_texture = nullptr;
}

Image::Image(const float & x, const float & y, const float & width, const float & height, const TextureImages * texture)
{
    this->_x = x;
    this->_y = y;
    this->_width = width;
    this->_height = height;
    this->_color = glm::vec4(1.0f);
    this->_texture = texture;
}

void Image::Draw()
{

}

void Image::Point(const float & x, const float & y)
{
    this->_x = x;
    this->_y = y;
}