#ifndef TEXTUREIMAGES_HPP
#define TEXTUREIMAGES_HPP

#include <iostream>

//! TextureImages class
/*!
    Stores the teture data for images
*/
class TextureImages
{
    public:
        /**
         * @brief Construct a new Texture Images object
         * 
         * 
         */
        TextureImages();
        /**
         * @brief Construct a new Texture Images object
         * 
         * @param file , is the file path of the image
         */
        TextureImages(const std::string & file);
        TextureImages(const TextureImages & src);
        ~TextureImages();
        /**
         * @brief Binds the texture in memory to be used when drawn
         * 
         */
        void Bind();
        void Load(const std::string & file);
        TextureImages & operator=(const TextureImages & src);
    private:
        void Init();
        std::string _file;
        unsigned int _ID;
        unsigned char * _data;
        int _height;
        int _width;
        int _channel;
};

#endif