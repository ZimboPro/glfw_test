#include <Shaders.hpp>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>

Shaders::Shaders(const std::string & vertexpath, const std::string & fragpath)
{
	std::string const vertexShader = GetSource(vertexpath);
    std::string const fragmentShader = GetSource(fragpath);
    if(vertexShader.size() == 0 || fragmentShader.size() == 0)
        throw std::logic_error("Empty shader files");
	
    this->_ID = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader.c_str());
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader.c_str());

	CreateShaderProgam(vs,fs);
}

Shaders::~Shaders()
{}

std::string const & Shaders::GetSource(const std::string & path)
{
    std::ifstream file(path);

    if (!file.good())
    {
        std::cout << path << " does not exist" << std::endl;
        return NULL;
    }

    std::string line;
    std::stringstream ss;
    while (getline(file, line))
        ss << line << std::endl;
    return ss.str();
}

void Shaders::CreateShaderProgam(int vs, int fs)
{
    glAttachShader(this->_ID, vs);
	glAttachShader(this->_ID, fs);
	glLinkProgram(this->_ID);
	glValidateProgram(this->_ID);

	glDeleteShader(vs);
	glDeleteShader(fs);
}

unsigned int Shaders::CompileShader(unsigned int type, const char * src)
{
    unsigned int id = glCreateShader(type);
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

inline void Shaders::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(this->_ID, name.c_str()), (int)value);
}

inline void Shaders::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(this->_ID, name.c_str()), value);
}

inline void Shaders::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(this->_ID, name.c_str()), value);
}

void Shaders::use()
{
	glUseProgram(this->_ID);
}

inline unsigned int Shaders::ID() const
{
	return this->_ID;
}
