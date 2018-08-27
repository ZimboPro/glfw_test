#include <ModelGroup.hpp>
#include <Shaders.hpp>

ModelGroup::ModelGroup()
{}

ModelGroup::~ModelGroup()
{
    this->_models.clear();
}

void ModelGroup::Draw(Shaders & shader, glm::mat4 projection, glm::mat4 view)
{
    shader.use();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    for (size_t i = 0; i < this->_models.size(); i++)
    {
        this->_models[i].Draw(shader);
    }
}