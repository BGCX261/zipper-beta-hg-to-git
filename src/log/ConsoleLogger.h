/* 
 * File:   ConsoleLogger.h
 * Author: Daniela
 *
 * Created on March 21, 2013, 7:08 PM
 */

#ifndef CONSOLELOGGER_H
#define	CONSOLELOGGER_H
#include "Logger.h"

/**
 * Logger that logs information in the console.
 */
class ConsoleLogger : public Logger
{
public:
    ConsoleLogger();
    ConsoleLogger(const ConsoleLogger& orig);
    virtual ~ConsoleLogger();
    void log(LoggingLevel level, unsigned int threadID, const char* source, char* msg);
};

#endif	/* CONSOLELOGGER_H */

