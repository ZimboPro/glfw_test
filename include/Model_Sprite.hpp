#ifndef MODEL_SPRITE_HPP
#define MODEL_SPRITE_HPP

#include <iostream>
#include <vector>
#include <Structs.hpp>

class Model_Texture;
class Shaders;
class Camera;

//! Model_Sprite class
/*!
    Handles the position, scale and rotation of the model.
    Alos renders the model
*/

class Model_Sprite
{
    public:
        /**
         * @brief Construct a new Model Sprite object
         * 
         */
        Model_Sprite();
        /**
         * @brief Construct a new Model_Sprite object
         * 
         * @param src The instance to copy
         */
        Model_Sprite(const Model_Sprite & src);
        /**
         * @brief Construct a new Model Sprite object
         * 
         * @param Model_Texture 
         */
        Model_Sprite(Model_Texture & Model_Texture);
        /**
         * @brief Construct a new Model Sprite object
         * 
         * @param path 
         */
        Model_Sprite(char * path);
        ~Model_Sprite();
        /**
         * @brief Assign the data in the right instance to the left
         * 
         * @param src 
         * @return Model_Sprite& 
         */
        Model_Sprite & operator=(const Model_Sprite & src);
        /**
         * @brief Load the model texture
         * 
         * @param Model_Texture 
         */
        void LoadModel_Texture(Model_Texture & Model_Texture);
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
         * @brief Draws the model
         * 
         * @param shader 
         */
        void DrawScaledBy(const Shaders & shader, float scale);

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
        glm::vec3 GetPosition() const;
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

        /**
         * @brief If Model texture is loaded
         * 
         * @return true 
         * @return false 
         */
        bool IsLoaded() const;


    private:
        Model_Texture * _Model_Texture;
        bool _gammaCorrection;
        bool _delete;

        glm::vec3 _scale;
        glm::vec3 _position;
        glm::mat4 _transformationMatrix;
        float _degrees;

        friend class ModelGroup;
};

#endif