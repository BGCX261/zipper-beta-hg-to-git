/* 
 * File:   Logger.cpp
 * Author: Daniela Meneses
 * 
 * Created on March 14, 2013, 8:41 PM
 */

#include "Logger.h"
#include "string.h"

char* Logger::getCurrentTime()
{
    time_t rawtime;
    time(&rawtime);
    char* time = asctime(localtime(&rawtime));
    time[strlen(time) - 1] = '\0';
    return time;
}

char* Logger::loggingLevelToString(LoggingLevel level)
{
    switch (level)
    {
    case ERROR: return "ERROR";
    case WARN: return "WARN";
    case INFO: return "INFO";
    case DEBUG: return "DEBUG";
    }
    return "";
}
