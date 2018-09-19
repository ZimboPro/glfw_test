#include <Log.hpp>
#include <sys/stat.h>
#include <time.h>
#include <fstream>

std::string Log::_path;

void Log::Init()
{
    if (_path.size() == 0)
    {
        mkdir("Log", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        time_t rawtime;
        struct tm * timeinfo;
        char buffer [80];

        time (&rawtime);
        timeinfo = localtime (&rawtime);

        strftime (buffer,80,"%F--%T",timeinfo);
        std::string time(buffer);
        _path = "Log/" + time + ".log";
        std::cout << _path << std::endl;
        std::ofstream file(_path);
        file << "Start of Log" << std::endl << std::endl;
        file.close();
    }
}

void Log::Event(const std::string & str)
{
    if (_path.size() == 0)
        Init();
    std::ofstream file;
    file.open(_path, std::ios::app);
    file << str << std::endl;
    file.close();
}