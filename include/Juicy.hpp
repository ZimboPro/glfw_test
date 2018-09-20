#ifndef JUICY_HPP
#define JUICY_HPP

#include <glm/glm.hpp>

class Model_Sprite;

class Juicy
{
    public:
        /**
         * @brief Moves the model from it's current point to the destination
         * 
         * @param model 
         * @param destination 
         * @param weighting 
         */
        static void Tweening(Model_Sprite & model, glm::vec3 & destination, float weighting);
        /**
         * @brief Rotates the model from it's current rotation to the final rotation
         * 
         * @param model 
         * @param rotation 
         * @param weighting 
         */
        static void TweeingRotation(Model_Sprite & model, float rotation, float weighting);
};

#endif