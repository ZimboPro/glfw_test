#ifndef GRAPHICSERRORS_HPP
#define GRAPHICSERRORS_HPP

#include <string>
#include <stdexcept>

class GraphicsErrors
{
    public:
        class ExceptionTemplate : public std::exception
        {
            public:
                ExceptionTemplate(const std::string& msg) : std::exception()
                {
                    e_msg = msg;
                }

                virtual const char* what() const throw()
                {
                    return e_msg.c_str();
                }

            private:
                std::string e_msg;
        };
        class FileDoesntExist : public ExceptionTemplate
        {
            public:
                FileDoesntExist(const std::string& msg) : ExceptionTemplate(std::string("File doesn't exist: ") + msg)
                {}
        };

        class IncorrectFileFormat : public ExceptionTemplate
        {
            public:
                IncorrectFileFormat(const std::string& msg) : ExceptionTemplate(std::string("Incorrectly Formated File: ") + msg)
                {}
        };

        class AssimpError : public ExceptionTemplate
        {
            public:
                AssimpError(const std::string& msg) : ExceptionTemplate(std::string("Assimp Error: ") + msg)
                {}
        };

        class TextureFailed : public ExceptionTemplate
        {
            public:
                TextureFailed(const std::string& msg) : ExceptionTemplate(std::string("Texture failed to Load: ") + msg)
                {}
        };

        class TextureNotLoaded : public ExceptionTemplate
        {
            public:
                TextureNotLoaded(const std::string& msg) : ExceptionTemplate(std::string("Texture not loaded: ") + msg)
                {}
        };
};

#endif