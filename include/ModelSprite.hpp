#ifndef MODELSPRITE_HPP
#define MODELSPRITE_HPP

#include <iostream>
#include <vector>
#include <Structs.hpp>

class ModelTexture;
class Shaders;
class Camera;

//! ModelSprite class
/*!
    Handles the position, scale and rotation of the model.
    Alos renders the model
*/

class ModelSprite
{
    public:
        /**
         * @brief Construct a new Model Sprite object
         * 
         */
        ModelSprite();
        /**
         * @brief Construct a new Model Sprite object
         * 
         * @param modelTexture 
         */
        ModelSprite(ModelTexture & modelTexture);
        ~ModelSprite();

        /**
         * @brief Load the model texture
         * 
         * @param modelTexture 
         */
        void LoadModelTexture(ModelTexture & modelTexture);
        /**
         * @brief Set the Gamma object
         * 
         * @param gamma default set to false
         */
        void SetGamma(bool gamma = false);

        /**
         * @brief Draws the model according to the specified view
         * 
         * @param shader 
         * @param perspective perpective wanted
         * @param view the camera view
         */
        void DrawView(Shaders & shader, glm::mat4 perspective, glm::mat4 view);
        /**
         * @brief Draws the model
         * 
         * @param shader 
         */
        void Draw(const Shaders & shader);

        /**
         * @brief Sets the position of the model
         * 
         * @param position 
         */
        void Position(const glm::vec3 & position);
        /**
         * @brief Sets the position of the model
         * 
         * @param x 
         * @param y 
         * @param z 
         */
        void Position(const float &x, const float &y, const float &z = 0);

        /**
         * @brief Sets the model scale
         * 
         * @param scale 
         */
        void Scale(const glm::vec3 & scale);
        /**
         * @brief Sets the model scale
         * 
         * @param scale 
         */
        void Scale(const float & scale);

        /**
         * @brief Sets the Rotaion
         * 
         * @param degrees 
         */
        void Rotate(const float & degrees);
        /**
         * @brief Sets the Rotaion according to the specified axis
         * 
         * @param degrees 
         * @param axis 
         */
        void Rotate(const float & degrees, const glm::vec3 & axis);
        
        /**
         * @brief Resets the position, scale and rotation
         * 
         */
        void Reset();

        /**
         * @brief Moves and updates the model's position, scale and rotation
         * 
         * @param x 
         * @param y 
         * @param z 
         * @param degree 
         */
        void Move(const float &x, const float &y, const float &z = 0, const float & degree = 0);

        /**
         * @brief Get the Postion object
         * 
         * @return glm::vec3 
         */
        glm::vec3 GetPostion() const;
        /**
         * @brief Get the Scale object
         * 
         * @return glm::vec3 
         */
        glm::vec3 GetScale() const;
        /**
         * @brief Get the Rotation object
         * 
         * @return float 
         */
        float GetRotation() const;


    private:
        ModelTexture * _modelTexture;
        bool _gammaCorrection;

        glm::vec3 _scale;
        glm::vec3 _position;
        glm::mat4 _transformationMatrix;
        float _degrees;

        friend class ModelGroup;
};

#endif