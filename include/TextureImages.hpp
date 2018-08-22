#ifndef TEXTUREIMAGES_HPP
#define TEXTUREIMAGES_HPP

#include <iostream>

class TextureImages
{
    public:
        TextureImages(const std::string & file);
        ~TextureImages();

        void Load();
        void Bind();
    private:
        std::string _file;
        unsigned int _ID;
        unsigned char * _data;
        int _height;
        int _width;
        int _channel;
};

#endif