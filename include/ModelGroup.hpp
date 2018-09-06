#ifndef MODELGROUP_HPP
#define MODELGROUP_HPP

#include <vector>
#include <ModelSprite.hpp>
#include <glm/glm.hpp>

class Shaders;

//! ModelGroup Class
/*!
    Stores a vector of ModelSprites and their positions will be relative to the
    position of ModelGroup
*/

class ModelGroup
{
    public:
        /**
         * @brief Construct a new Model Group object
         * 
         */
        ModelGroup();
        ~ModelGroup();

        /**
         * @brief The vector of stored ModelSprites
         * 
         */
        std::vector<ModelSprite> _models;
        /**
         * @brief Draws models according to the specified projection and view
         * 
         * @param shader 
         * @param projection 
         * @param view 
         */
        void DrawView(Shaders & shader, glm::mat4 projection, glm::mat4 view);
        /**
         * @brief Draws all the models
         * 
         * @param shader 
         */
        void Draw(Shaders & shader);

        /**
         * @brief Sets the ModelGroup position
         * 
         * @param position 
         */
        void Position(const glm::vec3 & position);
        /**
         * @brief Sets the ModelGroup position
         * 
         * @param x 
         * @param y 
         * @param z 
         */
        void Position(const float &x, const float &y, const float &z = 0);
    
    private:
        glm::vec3 _position;
};

#endif