#include <Juicy.hpp>
#include <Model_Sprite.hpp>

void Juicy::Tweening(Model_Sprite & model, glm::vec3 & destination, float weighting)
{
    glm::vec3 moveBy = (destination - model.GetPosition()) * weighting;
    model.Move(moveBy.x, moveBy.z, moveBy.y);
}

void Juicy::TweeingRotation(Model_Sprite & model, float rotation, float weighting)
{
    float rotateBy = (rotation - model.GetRotation()) * weighting;
    model.Move(0, 0, 0, rotateBy);
}