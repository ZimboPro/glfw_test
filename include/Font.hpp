#ifndef FONT_HPP
#define FONT_HPP

#include <map>
#include <Models.hpp>

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
        static std::map<char, Model *> _letters;
        static std::map<char, float> _space;
};

#endif