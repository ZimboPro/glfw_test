#include "../include/Shaders.hpp"
#include "../libogd/include/GLFW/glfw3.h"
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>

Shaders::Shaders(){}

Shaders::~Shaders(){}

std::string const & Shaders::GetSource(const std::string & path)
{
    std::ifstream file(path);

    if (!file.good())
    {
        std::cout << path << " does not exist" << std::endl;
        return "";
    }

    std::string line;
    std::stringstream ss;
    while (getline(file, line))
    {
        ss << line << "\n";
    }
    return ss.str();
}

unsigned int Shaders::CreateShaderProgam()
{
    
    std::string const vertexShader = GetSource("Resources/VertexShaders/Basic.vshader");
    std::string const fragmentShader = GetSource("Resources/FragmentShaders/Basic.fshader");
    if(vertexShader.size() == 0 || fragmentShader.size() == 0)
        return 0;
    unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);
	
	return program;
}

unsigned int Shaders::CompileShader(unsigned int type, const std::string & source)
{
    unsigned int id = glCreateShader(type);
	const char * src = source.c_str();
	glShaderSource(id, 1, &src, NULL); 
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	char infoLog[512];
	if (result == GL_FALSE)
	{
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::"<< (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")  << "::COMPILATION_FAILED\n" << infoLog << std::endl;
		glDeleteShader(id);
        return 0;
	}
	return id;
}
