#ifndef SHADERS_HPP
#define SHADERS_HPP

#include <iostream>

class Shaders
{
    public:
        Shaders();
        ~Shaders();

        static unsigned int CreateShaderProgam();
    
    private:
        static unsigned int CompileShader(unsigned int type, const std::string & source);
        static std::string const & GetSource(const std::string & path);
};

#endif