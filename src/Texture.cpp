#include <Texture.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/glad.h>

Texture::Texture(const std::string & file)
{
    this->_file = file;
    stbi_set_flip_vertically_on_load(true);
    Load();
}

Texture::~Texture()
{}

void Texture::Load()
{
    glGenTextures(1, &this->_ID);
    glBindTexture(GL_TEXTURE_2D, this->_ID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if(this->_file.find(".jpg") != std::string::npos)
        this->_data = stbi_load(this->_file.c_str(), &this->_width, &this->_height, &this->_channel, 0);
    else if (this->_file.find(".png") != std::string::npos)
        this->_data = stbi_load(this->_file.c_str(), &this->_width, &this->_height, &this->_channel, 0);
    
    if (!this->_data)
    {
        std::cout << "Error loading image" << std::endl;
    }
    else
    {
        
        if(this->_file.find(".jpg") != std::string::npos)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->_width, this->_height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->_data);
        else if (this->_file.find(".png") != std::string::npos)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->_width, this->_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->_data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(this->_data);
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, this->_ID);
}
