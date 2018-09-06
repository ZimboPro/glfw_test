#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>

//! Log Class
/*!
    Logs events into a file of the date and time of execution
    in a Logs folder in the same directory of the program
*/
class Log
{
    public:
    /**
     * @brief Log the event
     * 
     * @param str string that needs to be logged
     */
        static void Event(const std::string & str);
    
    private:
        static void Init();
        Log();
        ~Log();

        static std::string _path;
};

#endif