#ifndef TEXTUREIMAGES_HPP
#define TEXTUREIMAGES_HPP

#include <iostream>

class TextureImages
{
    public:
        TextureImages(const std::string & file);
        ~TextureImages();

        void Bind();
    private:
        void Load();
        std::string _file;
        unsigned int _ID;
        unsigned char * _data;
        int _height;
        int _width;
        int _channel;
};

#endif