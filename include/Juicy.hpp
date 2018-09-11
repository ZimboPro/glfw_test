#ifndef JUICY_HPP
#define JUICY_HPP

#include <glm/glm.hpp>

class Model_Sprite;

class Juicy
{
    public:
        static void Tweening(Model_Sprite & model, glm::vec3 & destination, float weighting);
        static void TweeingRotation(Model_Sprite & model, float rotation, float weighting);
};

#endif