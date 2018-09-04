#ifndef FONT_HPP
#define FONT_HPP

#include <map>
#include <ModelTexture.hpp>
#include <ModelSprite.hpp>

class Camera;
class Shaders;

class Font
{
    public:
        static void Draw(Shaders & shader, Camera & camera, int width, int height, const std::string & str, float x, float y, float scale);
        static void Load();

    private:
        Font();
        ~Font();
        static void LoadModels(char b, char e);
        static std::map<char, ModelSprite *> _letters;
        static std::map<char, float> _space;
};

#endif