#ifndef GTK4_LOGGER_H
#define GTK4_LOGGER_H

#include <fstream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "Definitions.h"

class Logger
{
public:
    explicit Logger(std::string);
    ~Logger();
    void debug(const std::string&);
    void info(const std::string&);
    void warn(const std::string&);
    void error(const std::string&);
private:
    void writeMessage(const std::string&, LogType logType);
    static std::string logName();

    std::string m_unitName;
};


#endif //GTK4_LOGGER_H
