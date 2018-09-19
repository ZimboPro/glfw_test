#include <TextureImages.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/glad.h>
#include <Coplien.hpp>

TextureImages::TextureImages()
{
    stbi_set_flip_vertically_on_load(true);
    Init();
}

TextureImages::TextureImages(const std::string & file)
{
    stbi_set_flip_vertically_on_load(true);
    Init();
    Load(file);
}

TextureImages::TextureImages(const TextureImages & src)
{
    *this = src;
}

TextureImages::~TextureImages()
{
    glDeleteTextures(1, &this->_ID);
}

TextureImages & TextureImages::operator=(const TextureImages & src)
{
    if (this != &src)
    {
        copy(this->_file, src._file);
        copy(this->_data, src._data);
        copy(this->_ID, src._ID);
        copy(this->_height, src._height);
        copy(this->_width, src._width);
        copy(this->_channel, src._channel);
    }
    return *this;
}

void TextureImages::Init()
{
    glGenTextures(1, &this->_ID);
    glBindTexture(GL_TEXTURE_2D, this->_ID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void TextureImages::Load(const std::string & file)
{
    this->_file = file;
    this->_data = stbi_load(this->_file.c_str(), &this->_width, &this->_height, &this->_channel, 0);
    
    if (!this->_data)
        std::cout << "Error loading image" << std::endl;
    else
    {
        GLenum format = 0;
        if (this->_channel == 1)
            format = GL_RED;
        else if (this->_channel == 3)
            format = GL_RGB;
        else if (this->_channel == 4)
            format = GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->_width, this->_height, 0, format, GL_UNSIGNED_BYTE, this->_data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(this->_data);
}

void TextureImages::Bind()
{
    glBindTexture(GL_TEXTURE_2D, this->_ID);
}
