/* 
 * File:   ConsoleLogger.cpp
 * Author: Daniela
 * 
 * Created on March 21, 2013, 7:08 PM
 */

#include "ConsoleLogger.h"

ConsoleLogger::ConsoleLogger()
{
    this->loggingLevel_ = INFO;
}

ConsoleLogger::ConsoleLogger(const ConsoleLogger& orig)
{
}

ConsoleLogger::~ConsoleLogger()
{
}

void ConsoleLogger::log(LoggingLevel level, unsigned int threadID, const char* source, char* msg)
{
    if (level <= loggingLevel_)
    {
        char* time = getCurrentTime();
        char* levelStr = loggingLevelToString(level);
        printf("%s [%u] [%s] %s: %s\n", time, threadID, source, levelStr, msg);
    }
}
