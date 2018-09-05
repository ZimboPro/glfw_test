#include <Font3d.hpp>
#include <Shaders.hpp>
#include <Camera.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <cctype>

std::map<char, ModelSprite *> Font3d::_letters;
std::map<char, float> Font3d::_space;

Font3d::Font3d()
{}

Font3d::~Font3d()
{
    for( auto const& [key, val] : _letters)
    {
        delete val;
    }
    _letters.clear();
}

void Font3d::Draw(Shaders & shader, Camera & camera, int width, int height, const std::string & str, float x, float y, float scale)
{
    float xSpacing = (x - static_cast<float>(width >> 1)) / static_cast<float>(width >> 1);
    float ySpacing = (static_cast<float>(height >> 1) - y) / static_cast<float>(height >> 1);
    glm::vec3 view(0, 0 , 1);
    // float degreex = glm::orientedAngle(view, -camera.Front, glm::vec3(1, 0, 0));
    float degreex = glm::orientedAngle(glm::normalize(glm::vec2(camera.Front.y, camera.Front.z)), glm::normalize(glm::vec2(view.y, view.z)));
    float degreey = glm::orientedAngle(glm::normalize(glm::vec2(camera.Front.x, camera.Front.z)), glm::normalize(glm::vec2(view.x, view.z)));
    float degreez = glm::orientedAngle(glm::normalize(glm::vec2(camera.Front.x, camera.Front.y)), glm::normalize(glm::vec2(view.x, view.y)));
    glm::vec3 newPosition = camera.Position + camera.Front * 2.0f + camera.Up * 0.77f * ySpacing + camera.Right * xSpacing * 1.15f;
    float degreeX = glm::orientedAngle(glm::normalize(glm::vec2(newPosition.y, newPosition.z) - glm::vec2(camera.Position.y, camera.Position.z)), glm::normalize(glm::vec2(camera.Front.y, camera.Front.z)));
    newPosition = newPosition - camera.Right * xSpacing * 1.15f;

    for (size_t i = 0; i < str.size(); i++)
    {
        ModelSprite * temp = _letters[toupper(str.at(i))];
        temp->Reset();
        temp->Position(newPosition + camera.Right * xSpacing * 1.15f);
        temp->Scale(scale);
        temp->Rotate(glm::degrees(degreey), glm::vec3(0, 1, 0));
        temp->Rotate(glm::degrees(degreex + degreeX), glm::vec3(1, 0, 0));
        temp->Rotate(glm::degrees(degreez), glm::vec3(0, 0, 1));
        temp->Draw(shader);
        xSpacing += _space[toupper(str.at(i))] * scale;
    }
}

void Font3d::LoadModels(char b, char e)
{
    for (char c = b; c <= e; c++)
    {
        std::string p = "../Resources/fonts/" + std::string(1, c) + ".obj";
        ModelTexture temp(const_cast<char *>(p.c_str()));
        _letters[toupper(c)] = new ModelSprite(temp);
        _space[toupper(c)] = 5.0f;
        if (toupper(c) == 'I')
            _space[toupper(c)] = 2.0f;
    }
}

void Font3d::Load()
{
    LoadModels('a', 'z');
    LoadModels('0', '9');
}