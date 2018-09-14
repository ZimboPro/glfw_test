#ifndef GRAPHICSERRORS_HPP
#define GRAPHICSERRORS_HPP

#include <string>
#include <stdexcept>

class GraphicsErrors
{
    public:
        class FileDoesntExist : public std::exception
        {
            public:
                FileDoesntExist(const std::string& msg) : std::exception()
                {
                    e_msg = std::string("File doesn't exist: ") + msg;
                }
                virtual const char* what() const throw()
                {
                    return e_msg.c_str();
                }

            private:
                std::string e_msg;
        };

        class IncorrectFileFormat : public std::exception
        {
            public:
                IncorrectFileFormat(const std::string& msg) : std::exception()
                {
                    e_msg = std::string("Incorrectly Formated File: ") + msg;
                }
                virtual const char* what() const throw()
                {
                    return e_msg.c_str();
                }
            private:
                std::string e_msg;
        };

        class AssimpError : public std::exception
        {
            public:
                AssimpError(const std::string& msg) : std::exception()
                {
                    e_msg = std::string("Assimp Error: ") + msg;
                }
                virtual const char* what() const throw()
                {
                    return e_msg.c_str();
                }
            private:
                std::string e_msg;
        };

        class TextureFailed : public std::exception
        {
            public:
                TextureFailed(const std::string& msg) : std::exception()
                {
                    e_msg = std::string("Texture failed to Load: ") + msg;
                }
                virtual const char* what() const throw()
                {
                    return e_msg.c_str();
                }
            private:
                std::string e_msg;
        };
};

#endif