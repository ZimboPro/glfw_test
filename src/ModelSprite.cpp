#include <ModelSprite.hpp>
#include <ModelTexture.hpp>
#include <Shaders.hpp>
#include <Camera.hpp>

ModelSprite::ModelSprite()
{
    this->_modelTexture = nullptr;
    Position(0, 0);
    Scale(1);
    Rotate(0);
    SetGamma();
}

ModelSprite::ModelSprite(ModelTexture & modelTexture)
{
    Position(0, 0);
    Scale(1);
    Rotate(0);
    LoadModelTexture(modelTexture);
    SetGamma();
}

ModelSprite::~ModelSprite()
{}

void ModelSprite::LoadModelTexture(ModelTexture & modelTexture)
{
    this->_modelTexture = &modelTexture;
}

void ModelSprite::SetGamma(bool gamma)
{
    this->_gammaCorrection = gamma;
}

void ModelSprite::DrawView(Shaders & shader, glm::mat4 perspective, glm::mat4 view)
{
    shader.use();
    shader.setMat4("projection", perspective);
    shader.setMat4("view", view);
    Draw(shader);
}

void ModelSprite::Draw(const Shaders & shader)
{
    shader.setMat4("model", this->_transformationMatrix);
    this->_modelTexture->Draw(shader);
}

void ModelSprite::Position(const glm::vec3 & position)
{
    this->_position = position;
    this->_transformationMatrix = glm::translate(this->_transformationMatrix, this->_position);
}

void ModelSprite::Position(const float &x, const float &y, const float &z)
{
    this->_position = glm::vec3(x, z, y);
    this->_transformationMatrix = glm::translate(this->_transformationMatrix, this->_position);
}

void ModelSprite::Scale(const glm::vec3 & scale)
{
    this->_scale = scale;
    this->_transformationMatrix = glm::scale(this->_transformationMatrix, this->_scale);
}

void ModelSprite::Scale(const float & scale)
{
    this->_scale = glm::vec3(scale);
    this->_transformationMatrix = glm::scale(this->_transformationMatrix, this->_scale);
}

void ModelSprite::Reset()
{
    this->_transformationMatrix = glm::mat4(1.0f);
}

void ModelSprite::Rotate(const float & degrees)
{
    this->_degrees = degrees;
    this->_transformationMatrix = glm::rotate(this->_transformationMatrix, glm::radians(degrees), glm::vec3(0, 1, 0));
}

void ModelSprite::Rotate(const float & degrees, const glm::vec3 & axis)
{
    this->_transformationMatrix = glm::rotate(this->_transformationMatrix, glm::radians(degrees), axis);
}

void ModelSprite::Move(const float & x, const float & y, const float & z, const float & degree)
{
    Reset();
    this->_position += glm::vec3(x, z, y);
    Position(this->_position);
    Scale(this->_scale);
    this->_degrees += degree;
    Rotate(this->_degrees);
}