/* 
 * File:   Logger.cpp
 * Author: Daniela Meneses
 * 
 * Created on March 14, 2013, 8:41 PM
 */

#include "Logger.h"
#include "string.h"

const char* Logger::getCurrentTime()
{
    time_t rawtime;
    time(&rawtime);
    char* time = asctime(localtime(&rawtime));
    time[strlen(time) - 1] = '\0';
    return time;
}

const char* Logger::loggingLevelToString(LoggingLevel level)
{
    static char const *  loggingLevelsAsString[]={"ERROR", "WARN", "INFO", "DEBUG"};
    
    return loggingLevelsAsString[level];
}
