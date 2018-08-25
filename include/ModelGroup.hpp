#ifndef MODELGROUP_HPP
#define MODELGROUP_HPP

#include <vector>
#include <MultipleOfModel.hpp>
#include <glm/glm.hpp>

class Shaders;

class ModelGroup
{
    public:
        ModelGroup();
        ~ModelGroup();

        std::vector<MultipleOfModel> _models;
        void Draw(Shaders & shader, glm::mat4 projection, glm::mat4 view);
        
};

#endif