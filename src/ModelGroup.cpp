#include <ModelGroup.hpp>
#include <Shaders.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Model_Texture.hpp>
#include <Coplien.hpp>

ModelGroup::ModelGroup()
{
    this->_position = glm::vec3(0);
}

ModelGroup::ModelGroup(const ModelGroup & src)
{
    *this = src;
}

ModelGroup::~ModelGroup()
{
    for (size_t i = 0; i < this->_models.size(); i++)
        delete this->_models[i];
}

ModelGroup & ModelGroup::operator=(const ModelGroup & src)
{
    if (this != &src)
    {
        copy(this->_models, src._models);
        copy(this->_position, src._position);
    }
    return *this;
}

void ModelGroup::DrawView(Shaders & shader, glm::mat4 projection, glm::mat4 view)
{
    shader.use();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    for (size_t i = 0; i < this->_models.size(); i++)
    {
        this->_models[i]->Draw(shader);
    }
}

void ModelGroup::Draw(Shaders & shader)
{
    for (size_t i = 0; i < this->_models.size(); i++)
    {
        shader.setMat4("model", glm::translate(this->_models[i]->_transformationMatrix, this->_position));
        this->_models[i]->_Model_Texture->Draw(shader);
    }
}

void ModelGroup::Position(const glm::vec3 & position)
{
    this->_position = position;
}

void ModelGroup::Position(const float &x, const float &y, const float &z)
{
    this->_position = glm::vec3(x, z, y);
}

glm::vec3 ModelGroup::GetPosition() const
{
    return this->_position;
}

void ModelGroup::Move(const float &x, const float &y, const float &z)
{
    this->_position += glm::vec3(x, z, y); 
}