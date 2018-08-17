#ifndef SHADERS_HPP
#define SHADERS_HPP

#include <iostream>

class Shaders
{
    public:
        Shaders(const std::string & vertexpath, const std::string & fragpath);
        ~Shaders();

        void setBool(const std::string &name, bool value) const;  
        void setInt(const std::string &name, int value) const;   
        void setFloat(const std::string &name, float value) const;
        void use();
        unsigned int ID() const;
    
    private:
        void CreateShaderProgam(int vs, int fs);
        unsigned int CompileShader(unsigned int type, const char * src);
        std::string const & GetSource(const std::string & path);

        unsigned int _ID;
};

#endif