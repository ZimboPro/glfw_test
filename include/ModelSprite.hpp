#ifndef MODELSPRITE_HPP
#define MODELSPRITE_HPP

#include <iostream>
#include <vector>
#include <Structs.hpp>

class ModelTexture;
class Shaders;
class Camera;

class ModelSprite
{
    public:
        ModelSprite();
        ModelSprite(ModelTexture & modelTexture);
        ~ModelSprite();

        void LoadModelTexture(ModelTexture & modelTexture);
        void SetGamma(bool gamma = false);

        void DrawView(Shaders & shader, glm::mat4 perspective, glm::mat4 view);
        void Draw(const Shaders & shader);

        void Position(const glm::vec3 & position);
        void Position(const float &x, const float &y, const float &z = 0);

        void Scale(const glm::vec3 & scale);
        void Scale(const float & scale);

        void Rotate(const float & degrees);
        void Rotate(const float & degrees, const glm::vec3 & axis);
        
        void Reset();
        void Move(const float &x, const float &y, const float &z = 0, const float & degree = 0);

    private:
        ModelTexture * _modelTexture;
        bool _gammaCorrection;

        glm::vec3 _scale;
        glm::vec3 _position;
        glm::mat4 _transformationMatrix;
        float _degrees;
};

#endif