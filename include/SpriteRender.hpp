#ifndef SPRITERENDER_HPP
#define SPRITERENDER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <Shaders.hpp>

class TextureImages;

class SpriteRender
{
    public:
    // Constructor (inits shaders/shapes)
    SpriteRender(Shaders &shader);
    // Destructor
    ~SpriteRender();
    // Renders a defined quad textured with given sprite
    void DrawSprite(TextureImages &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
private:
    void Enable();
    void Disable();
    // Render state
    Shaders *_shader; 
    GLuint _quadVAO;
    // Initializes and configures the quad's buffer and vertex attributes
    void initRenderData();
};

#endif