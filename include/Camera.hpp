#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

class Shaders;

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL

//! Camera Class
/*!
 * @brief The Camera Class that is used to control where the camera view is
 * 
 */
class Camera
{
    public:
        // Camera Attributes
        glm::vec3 Position; /*!< Camera Postion */
        glm::vec3 Front; /*!< Camera View vector */
        glm::vec3 Up; /*!< Camera Up vector */
        glm::vec3 Right; /*!< Camera Right vector */
        glm::vec3 WorldUp; /*!< World Up vector */
        // Euler Angles
        float Yaw;
        float Pitch;
        // Camera options
        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;

        // Constructor with vectors
        //!Camera constructor
        /**
         * @brief Construct a new Camera object
         * 
         * @param position 
         * @param up 
         * @param yaw 
         * @param pitch 
         */
        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
        /**
         * @brief Construct a new Camera object
         * 
         * @param posX 
         * @param posY 
         * @param posZ 
         * @param upX 
         * @param upY 
         * @param upZ 
         * @param yaw 
         * @param pitch 
         */
        Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
        /**
         * @brief Get the View Matrix object produced by this instance of the camera
         * 
         * @return glm::mat4 
         */
        glm::mat4 GetViewMatrix();
        /**
         * @brief The point the camera must look at
         * 
         * @param point 
         */
        void LookAt(const glm::vec3 & point);
        /**
         * @brief Process the Keyboard and movement of the camera using the keyboard
         * 
         * @param direction 
         * @param deltaTime 
         */
        void ProcessKeyboard(Camera_Movement direction, float deltaTime);
        /**
         * @brief Process the Mouse Movement and change the view direction of camera
         * 
         * @param xoffset 
         * @param yoffset 
         * @param constrainPitch 
         */
        void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
        /**
         * @brief Process the Mouse Scroll and zooming in
         * 
         * @param yoffset 
         */
        void ProcessMouseScroll(float yoffset);
        /**
         * @brief Set the Shader View object
         * 
         * @param shader 
         * @param width 
         * @param height 
         */
        void SetShaderView(Shaders & shader, int width, int height);

        void Move(float &x, float &y, float &z);

    private:
        void updateCameraVectors();
};

#endif