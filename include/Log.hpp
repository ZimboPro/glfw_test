#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>

class Log
{
    public:
        static void Event(const std::string & str);
    
    private:
        static void Init();
        Log();
        ~Log();

        static std::string _path;
};

#endif