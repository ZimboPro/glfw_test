#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>

class Texture
{
    public:
        Texture(const std::string & file);
        ~Texture();

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