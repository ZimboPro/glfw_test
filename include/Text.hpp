#ifndef TEXT_HPP
#define TEXT_HPP

#include <glm/glm.hpp>
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glad/glad.h>

#include <map>

class Shaders;

struct Character {
    GLuint TextureID;   // ID handle of the glyph texture
    glm::ivec2 Size;    // Size of glyph
    glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
    GLuint Advance;    // Horizontal offset to advance to next glyph
};

class Text
{
    public:
        Text(const char * file);
        ~Text();

        void Load(const char * file);
        void Render(Shaders &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, int width, int height);
    
    private:
        std::map<GLchar, Character> _characters;
        unsigned int _VAO;
        unsigned int _VBO;
        FT_Library _ft;
        FT_Face _face;
};

#endif