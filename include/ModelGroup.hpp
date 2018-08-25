#ifndef MODELGROUP_HPP
#define MODELGROUP_HPP

#include <vector>

#include <MultipleOfModel.hpp>
class Shaders;

class ModelGroup
{
    public:
        ModelGroup();
        ~ModelGroup();

        std::vector<MultipleOfModel> _models;
        void Draw(Shaders & shader);
        
};

#endif