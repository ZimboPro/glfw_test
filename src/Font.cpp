#include <Font.hpp>
#include <Shaders.hpp>
#include <Camera.hpp>
#include <glm/gtx/vector_angle.hpp>

std::map<char, Model *> Font::_letters;
std::map<char, float> Font::_space;

Font::Font()
{
}

Font::~Font()
{
    _letters.clear();
}

void Font::Draw(Shaders & shader, Camera & camera, int width, int height, const std::string & str, float x, float y, float scale)
{
    float xSpacing = x;
    glm::vec3 view(0, 0 , 1);
    // float degreex = glm::orientedAngle(view, -camera.Front, glm::vec3(1, 0, 0));
    float degreex = glm::orientedAngle(glm::normalize(glm::vec2(camera.Front.y, camera.Front.z)), glm::normalize(glm::vec2(view.y, view.z)));
    float degreey = glm::orientedAngle(glm::normalize(glm::vec2(camera.Front.x, camera.Front.z)), glm::normalize(glm::vec2(view.x, view.z)));
    float degreez = glm::orientedAngle(glm::normalize(glm::vec2(camera.Front.x, camera.Front.y)), glm::normalize(glm::vec2(view.x, view.y)));
    // float degreez = glm::orientedAngle(view, -camera.Front, glm::vec3(0, 0, 1));
    std::cout << "x " << degreex << " y " << degreey << " z " << degreez << std::endl;
    std::cout << "x " << glm::degrees(degreex) << " y " << glm::degrees(degreey) << " z " << glm::degrees(degreez) << std::endl;
    for (size_t i = 0; i < str.size(); i++)
    {
        _letters[str.at(i)]->Reset();
        _letters[str.at(i)]->Position(glm::vec3(0, 0, 0));
        _letters[str.at(i)]->Scale(scale);
        _letters[str.at(i)]->Rotate(glm::degrees(degreey), glm::vec3(0, 1, 0));
        _letters[str.at(i)]->Rotate(glm::degrees(degreex), glm::vec3(1, 0, 0));
        _letters[str.at(i)]->Rotate(glm::degrees(degreez), glm::vec3(0, 0, 1));
        _letters[str.at(i)]->DrawAndSet(shader, "model");
        // xSpacing += _space[str.at(i)] * scale;
    }
}

void Font::Load()
{
    _letters['m'] = new Model(R"(../Resources/Assets/mario_walking_1.obj)");
}