#include <Image.hpp>
#include <Shaders.hpp>
#include <TextureImages.hpp>
#include <Camera.hpp>

Image::Image(const float & x, const float & y, const float & width, const float & height, const glm::vec4 & color, unsigned int windowWidth, unsigned int windowHeight)
{
    this->_color = color;
    this->_texture = nullptr;
    this->_WinHeight = windowHeight;
    this->_WinWidth = windowWidth;
    CalcPoints(x, y, width, height);
    
    LoadSquare();
}

void Image::CalcPoints(const float & x, const float & y, const float & width, const float & height)
{
    this->_xf = static_cast<float>(x - (this->_WinWidth >> 1)) / static_cast<float>(this->_WinWidth >> 1);
    this->_yf = static_cast<float>((this->_WinHeight >> 1) - y) / static_cast<float>(this->_WinHeight >> 1);
    this->_x1 = static_cast<float>(x - (this->_WinWidth >> 1) + width) / static_cast<float>(this->_WinWidth >> 1);
    this->_y1 = static_cast<float>((this->_WinHeight >> 1) - y - height) / static_cast<float>(this->_WinHeight >> 1);

    this->_indices[0] = 0;
    this->_indices[1] = 1;
    this->_indices[2] = 3;
    this->_indices[3] = 1;
    this->_indices[4] = 2;
    this->_indices[5] = 3;
}

Image::Image(const float & x, const float & y, const float & width, const float & height, TextureImages * texture, unsigned int windowWidth, unsigned int windowHeight)
{
    //glEnable(GL_BLEND); 
    this->_WinHeight = windowHeight;
    this->_WinWidth = windowWidth;
    CalcPoints(x, y, width, height);
    this->_color = glm::vec4(1.0f);
    this->_texture = texture;
    Load();
}

Image::~Image()
{
    glDeleteVertexArrays(1, &this->_vao);
    glDeleteBuffers(1, &this->_vbo);
    glDeleteBuffers(1, &this->_ebo);
}

void Image::Draw(Shaders & shader, Camera & camera)
{
    if (this->_texture != nullptr)
        this->_texture->Bind();
    shader.use();
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->_WinWidth), 0.0f, static_cast<GLfloat>(this->_WinHeight));
    // shader.setMat4("projection", glm::perspective(glm::radians(camera.Zoom), (float)this->_WinWidth / (float)this->_WinHeight , 1.0f, 100.0f));
    shader.setMat4("projection", projection);
    shader.setMat4("view", glm::mat4());
    glm::mat4 model(1.0f);
    // model = glm::translate(model, camera.Position);
    // model = glm::rotate(model, glm::radians(camera.Yaw), glm::vec3(0, 1, 0));
    // model = glm::rotate(model, glm::radians(camera.Pitch), glm::vec3(1, 0, 0));
    shader.setMat4Ptr("model", model);
    glBindVertexArray(this->_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Image::Load()
{
    float vertices[] = {
        // positions         // texture coords
         _x1, _yf, 0.0f,  1.0f, 1.0f, // top right
         _x1, _y1, 0.0f,  1.0f, 0.0f, // bottom right
         _xf, _y1, 0.0f,  0.0f, 0.0f, // bottom left
         _xf, _yf, 0.0f,  0.0f, 1.0f  // top left 
    };

    Bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    EnableVertex(3, 5); 
}

void Image::Bind()
{
    glGenVertexArrays(1, &this->_vao);
    glGenBuffers(1, &this->_vbo);
    glGenBuffers(1, &this->_ebo);

    glBindVertexArray(this->_vao);

    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
}

void Image::EnableVertex(int pointCount, int rowCount)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->_indices), this->_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, pointCount, GL_FLOAT, GL_FALSE, rowCount * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, rowCount - pointCount, GL_FLOAT, GL_FALSE, rowCount * sizeof(float), (void*)(pointCount * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Image::LoadSquare()
{
    float rf = this->_color.x;
    float gf = this->_color.y;
    float bf = this->_color.z;
    float vertices[] = {
        // positions         // color
         _x1, _yf, 0.0f,  rf, gf, bf,
         _x1, _y1, 0.0f,  rf, gf, bf,
         _xf, _y1, 0.0f,  rf, gf, bf,
         _xf, _yf, 0.0f,  rf, gf, bf
    };

    Bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    EnableVertex(3, 6);
}