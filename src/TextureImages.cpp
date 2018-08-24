#include <TextureImages.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/glad.h>

TextureImages::TextureImages(const std::string & file)
{
    this->_file = file;
    stbi_set_flip_vertically_on_load(true);
    Load();
}

TextureImages::~TextureImages()
{}

void TextureImages::Load()
{
    glGenTextures(1, &this->_ID);
    glBindTexture(GL_TEXTURE_2D, this->_ID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->_width, this->_height, 0, format, GL_UNSIGNED_BYTE, this->_data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(this->_data);
}

void TextureImages::Bind()
{
    glBindTexture(GL_TEXTURE_2D, this->_ID);
}
