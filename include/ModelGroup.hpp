#ifndef MODELGROUP_HPP
#define MODELGROUP_HPP

class MultipleOfModel;
class Shaders;

class ModelGroup
{
    public:
        ModelGroup();
        ~ModelGroup();

        void AddModel(MultipleOfModel & model);
        
};

#endif