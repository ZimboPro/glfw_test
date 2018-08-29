#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

#include <glad/glad.h>

class Texture2d
{
    public:
        GLuint ID;
        GLuint Width;
        GLuint Height;
        GLuint Internal_Format;
        GLuint Image_Format;

        GLuint Wrap_S;
        GLuint Wrap_T;
        GLuint Filter_Min;
        GLuint Filter_Max;
        // Constructor (sets default texture modes)
        Texture2d();
        ~Texture2d();
        // Generates texture from image data
        void Generate(GLuint width, GLuint height, unsigned char* data);
        // Binds the texture as the current active GL_TEXTURE_2D texture object
        void Bind() const;
};

#endif