#include <ModelGroup.hpp>
#include <Shaders.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ModelTexture.hpp>

ModelGroup::ModelGroup()
{
    this->_position = glm::vec3(0);
}

ModelGroup::~ModelGroup()
{
    this->_models.clear();
}

void ModelGroup::DrawView(Shaders & shader, glm::mat4 projection, glm::mat4 view)
{
    shader.use();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    for (size_t i = 0; i < this->_models.size(); i++)
    {
        this->_models[i].Draw(shader);
    }
}

void ModelGroup::Draw(Shaders & shader)
{
    for (size_t i = 0; i < this->_models.size(); i++)
    {
        shader.setMat4("model", glm::translate(this->_models[i]._transformationMatrix, this->_position));
        this->_models[i]._modelTexture->Draw(shader);
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