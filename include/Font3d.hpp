#ifndef FONT3D_HPP
#define FONT3D_HPP

#include <map>
#include <ModelTexture.hpp>
#include <ModelSprite.hpp>

class Camera;
class Shaders;

class Font3d
{
    public:
        static void Load();
        static void Draw(Shaders & shader, Camera & camera, int width, int height, const std::string & str, float x, float y, float scale);

    private:
        Font3d();
        ~Font3d();
        static void LoadModels(char b, char e);
        static std::map<char, ModelSprite *> _letters;
        static std::map<char, float> _space;
};

#endif