#include <Camera.hpp>
#include <iostream>
#include <Shaders.hpp>
#include <stdexcept>
#include <Coplien.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(const Camera & src)
{
    *this = src;
}

Camera::~Camera()
{}

Camera & Camera::operator=(const Camera & src)
{
    if (this != &src)
    {
        copy(this->Position, src.Position);
        copy(this->Front, src.Front);
        copy(this->Up, src.Up);
        copy(this->Right, src.Right);
        copy(this->WorldUp, src.WorldUp);
        copy(this->Yaw, src.Yaw);
        copy(this->Pitch, src.Pitch);
        copy(this->MovementSpeed, src.MovementSpeed);
        copy(this->MouseSensitivity, src.MouseSensitivity);
        copy(this->Zoom, src.Zoom);
    }
    return *this;
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw   += xoffset;
    Pitch += yoffset;

    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    if (Zoom >= 1.0f && Zoom <= 45.0f)
        Zoom -= yoffset;
    if (Zoom <= 1.0f)
        Zoom = 1.0f;
    if (Zoom >= 45.0f)
        Zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up    = glm::normalize(glm::cross(Right, Front));
}

void Camera::LookAt(const glm::vec3 & point)
{
    if (point == this->Position)
        throw std::logic_error("Look at point is the same as the camera Postion");
    Front = glm::normalize(point - Position);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Pitch = glm::degrees(asin(Front.y));
    Yaw = -glm::degrees(acos(Front.x / cos(glm::radians(Pitch))));
    Up  = glm::normalize(glm::cross(Right, Front));
}

void Camera::SetShaderView(Shaders & shader, int width, int height)
{
    glm::mat4 projection = glm::perspective(glm::radians(this->Zoom), (float)width / (float)height, 0.1f, 100.0f);
    shader.use();
    shader.setMat4("projection", projection);
    shader.setMat4("view", GetViewMatrix());
}

void Camera::Move(float &x, float &y, float &z)
{
    Position += glm::vec3(x, z, y);
}