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
//! Text class
/*!
    Used to store the font data and render the text
*/
class Text
{
    public:
        /**
         * @brief Construct a new Text object
         * 
         */
        Text();
        /**
         * @brief Construct a new Text object
         * 
         * @param file is the file path to the font data file
         */
        Text(const char * file);
        ~Text();
        /**
         * @brief Loads the font data file
         * 
         * @param file is the file path to the font data file
         */
        void Load(const char * file);
        /**
         * @brief Renders the text, Origin is the lower left corner
         * 
         * @param shader 
         * @param text 
         * @param x 
         * @param y 
         * @param scale 
         * @param color 
         * @param width of the window
         * @param height of the window
         */
        void Render(Shaders &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, int width, int height);
    
    private:
        void Enable();
        void Disable();

        std::map<GLchar, Character> _characters;
        unsigned int _VAO;
        unsigned int _VBO;
        FT_Library _ft;
        FT_Face _face;
};

#endif