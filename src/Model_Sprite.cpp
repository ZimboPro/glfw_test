#include <Model_Sprite.hpp>
#include <Model_Texture.hpp>
#include <Shaders.hpp>
#include <Camera.hpp>
#include <Coplien.hpp>

Model_Sprite::Model_Sprite()
{
    this->_Model_Texture = nullptr;
    this->_delete = false;
    Position(0, 0);
    Scale(1);
    Rotate(0);
    SetGamma();
}

Model_Sprite::Model_Sprite(const Model_Sprite & src)
{
    *this = src;
}

Model_Sprite::Model_Sprite(char * path)
{
    this->_Model_Texture = new Model_Texture(path);
    this->_delete = true;
    Position(0, 0);
    Scale(1);
    Rotate(0);
    SetGamma();
}

Model_Sprite::Model_Sprite(Model_Texture & Model_Texture)
{
    Position(0, 0);
    Scale(1);
    Rotate(0);
    LoadModel_Texture(Model_Texture);
    SetGamma();
    this->_delete = false;
}

Model_Sprite::~Model_Sprite()
{
    if (this->_delete)
        delete this->_Model_Texture;
}

Model_Sprite & Model_Sprite::operator=(const Model_Sprite & src)
{
    if (this != & src)
    {
        copy(*this->_Model_Texture, *src._Model_Texture);
        copy(this->_gammaCorrection, src._gammaCorrection);
        copy(this->_delete, src._delete);
        copy(this->_scale, src._scale);
        copy(this->_position, src._position);
        copy(this->_transformationMatrix, src._transformationMatrix);
        copy(this->_degrees, src._degrees);
    }
    return *this;
}

void Model_Sprite::LoadModel_Texture(Model_Texture & Model_Texture)
{
    this->_Model_Texture = &Model_Texture;
}

void Model_Sprite::SetGamma(bool gamma)
{
    this->_gammaCorrection = gamma;
}

void Model_Sprite::DrawView(Shaders & shader, glm::mat4 perspective, glm::mat4 view)
{
    shader.use();
    shader.setMat4("projection", perspective);
    shader.setMat4("view", view);
    Draw(shader);
}

void Model_Sprite::Draw(Shaders & shader)
{
    shader.setMat4("model", this->_transformationMatrix);
    this->_Model_Texture->Draw(shader);
}

void Model_Sprite::DrawScaledBy(Shaders & shader, float scale)
{
    shader.setMat4("model", glm::scale(this->_transformationMatrix, glm::vec3(scale)));
    this->_Model_Texture->Draw(shader);
}

void Model_Sprite::Position(const glm::vec3 & position)
{
    this->_position = position;
    this->_transformationMatrix = glm::translate(this->_transformationMatrix, this->_position);
}

void Model_Sprite::Position(const float &x, const float &y, const float &z)
{
    this->_position = glm::vec3(x, z, y);
    this->_transformationMatrix = glm::translate(this->_transformationMatrix, this->_position);
}

void Model_Sprite::Scale(const glm::vec3 & scale)
{
    this->_scale = scale;
    this->_transformationMatrix = glm::scale(this->_transformationMatrix, this->_scale);
}

void Model_Sprite::Scale(const float & scale)
{
    this->_scale = glm::vec3(scale);
    this->_transformationMatrix = glm::scale(this->_transformationMatrix, this->_scale);
}

void Model_Sprite::Reset()
{
    this->_transformationMatrix = glm::mat4(1.0f);
}

void Model_Sprite::Rotate(const float & degrees)
{
    this->_degrees = degrees;
    this->_transformationMatrix = glm::rotate(this->_transformationMatrix, glm::radians(degrees), glm::vec3(0, 1, 0));
}

void Model_Sprite::Rotate(const float & degrees, const glm::vec3 & axis)
{
    this->_transformationMatrix = glm::rotate(this->_transformationMatrix, glm::radians(degrees), axis);
}

void Model_Sprite::Move(const float & x, const float & y, const float & z, const float & degree)
{
    Reset();
    this->_position += glm::vec3(x, z, y);
    Position(this->_position);
    Scale(this->_scale);
    this->_degrees += degree;
    Rotate(this->_degrees);
}

glm::vec3 Model_Sprite::GetPosition() const
{
    return this->_position;
}

glm::vec3 Model_Sprite::GetScale() const
{
    return this->_scale;
}

float Model_Sprite::GetRotation() const
{
    return this->_degrees;
}

bool Model_Sprite::IsLoaded() const
{
    return this->_Model_Texture != nullptr;
}