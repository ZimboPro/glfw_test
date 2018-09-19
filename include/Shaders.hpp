#ifndef SHADERS_HPP
#define SHADERS_HPP

#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
//! Shaders class
/*!
    Handles the shaders used on the GPU
*/
class Shaders
{
    public:
        /**
         * @brief Construct a new Shaders object
         * 
         * @param vertexpath to the Vertex Shader file
         * @param fragpath to the Fragment Shader file
         */
        Shaders(const std::string & vertexpath, const std::string & fragpath);
        Shaders(const Shaders & src);
        ~Shaders();

        Shaders & operator=(const Shaders & src);

        /**
         * @brief Binds the the shader
         * 
         */
        void use();
        /**
         * @brief Returns the Shader ID
         * 
         * @return unsigned int 
         */
        unsigned int ID() const;
        
        /**
         * @brief Set the Bool value
         * 
         * @param name 
         * @param value 
         */
        void setBool(const std::string &name, bool value) const;
        /**
         * @brief Set the Int value
         * 
         * @param name 
         * @param value 
         */
        void setInt(const std::string &name, int value) const;
        /**
         * @brief Set the Float value
         * 
         * @param name 
         * @param value 
         */
        void setFloat(const std::string &name, float value) const;
        /**
         * @brief Set the Vec2 value
         * 
         * @param name 
         * @param value 
         */
        void setVec2(const std::string &name, const glm::vec2 &value) const;
        /**
         * @brief Set the Vec2 value
         * 
         * @param name 
         * @param x 
         * @param y 
         */
        void setVec2(const std::string &name, float x, float y) const;
        /**
         * @brief Set the Vec3 value
         * 
         * @param name 
         * @param value 
         */
        void setVec3(const std::string &name, const glm::vec3 &value) const;
        /**
         * @brief Set the Vec3 value
         * 
         * @param name 
         * @param x 
         * @param y 
         * @param z 
         */
        void setVec3(const std::string &name, float x, float y, float z) const;
        /**
         * @brief Set the Vec4 value
         * 
         * @param name 
         * @param value 
         */
        void setVec4(const std::string &name, const glm::vec4 &value) const;
        /**
         * @brief Set the Vec4 value
         * 
         * @param name 
         * @param x 
         * @param y 
         * @param z 
         * @param w 
         */
        void setVec4(const std::string &name, float x, float y, float z, float w) const;

        /**
         * @brief Set the Mat2 value
         * 
         * @param name 
         * @param mat 
         */
        void setMat2(const std::string &name, const glm::mat2 &mat) const;

        /**
         * @brief Set the Mat3 value
         * 
         * @param name 
         * @param mat 
         */
        void setMat3(const std::string &name, const glm::mat3 &mat) const;
        /**
         * @brief Set the Mat4 value
         * 
         * @param name 
         * @param mat 
         */
        void setMat4(const std::string &name, const glm::mat4 &mat) const;
        /**
         * @brief Set the Mat4 Ptr value
         * 
         * @param name 
         * @param mat 
         */
        void setMat4Ptr(const std::string &name, const glm::mat4 &mat) const;
    
    private:
        void CreateShaderProgam(int vs, int fs);
        unsigned int CompileShader(unsigned int type, const char * src);
        std::string const GetSource(const std::string & path);

        unsigned int _ID;
};

#endif