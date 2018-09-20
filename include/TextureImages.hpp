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
        /**
         * @brief Construct a new Texture Images object and loads the texture automatically
         * 
         * @param src The instance to copy
         */
        TextureImages(const TextureImages & src);
        ~TextureImages();
        /**
         * @brief Binds the texture in memory to be used when drawn
         * 
         */
        void Bind();
        /**
         * @brief Load the texture into memory
         * 
         * @param file 
         */
        void Load(const std::string & file);
        /**
         * @brief Assign the data in the right instance to the left
         * 
         * @param src 
         * @return TextureImages& 
         */
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