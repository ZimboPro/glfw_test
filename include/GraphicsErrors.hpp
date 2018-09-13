#ifndef GRAPHICSERRORS_HPP
#define GRAPHICSERRORS_HPP

#include <string>
#include <exception>

class GraphicsErrors
{
    public:
        class FileDoesntExist : public std::logic_error
        {
            public:
                FileDoesntExist(const std::string& msg) : logic_error(std::string("File doesn't exist: ") + msg)
                {}
        };

        class IncorrectFileFormat : public std::logic_error
        {
            public:
                IncorrectFileFormat(const std::string& msg) : logic_error(std::string("Incorrectly Formated File: ") + msg)
                {}
        };

        class AssimpError : public std::logic_error
        {
            public:
                AssimpError(const std::string& msg) : logic_error(std::string("Assimp Error: ") + msg)
                {}
        };

        class TextureFailed : public std::logic_error
        {
            public:
                TextureFailed(const std::string& msg) : logic_error(std::string("Texture failed to Load: ") + msg)
                {}
        };
};

#endif