/* 
 * File:   Logger.h
 * Author: Daniela Meneses
 *
 * Created on March 14, 2013, 8:41 PM
 */
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string>

#ifndef LOGGER_H
#define	LOGGER_H

/**
 * Logging levels enum. Define logging levels for the [Logger Class](@ref Logger)
 */
enum LoggingLevel
{
    ERROR = 0, WARN, INFO, DEBUG
};

/**
 * Logs information in different levels.
 */
class Logger
{
public:
    /**
     * Logs the received message. If the logging level is higher than the defined 
     * in the logger won't be logged.
     * 
     * @param level Log level
     * @param msg Message to log
     */
    virtual void log(LoggingLevel level, unsigned int threadID, const char* source, char* msg) = 0;

    /**
     * Return the default logging level.
     * 
     * @return Default logging level
     */
    LoggingLevel getLoggingLevel() const
    {
        return loggingLevel_;
    }

    /**
     * Change the default logging level.
     * 
     * @param loggingLevel New logging level
     */
    void setLoggingLevel(LoggingLevel loggingLevel)
    {
        this->loggingLevel_ = loggingLevel;
    }
protected:
    const char* loggingLevelToString(LoggingLevel level);
    const char* getCurrentTime();

    /**
     * Define the minimum logging level for this logger.
     */
    LoggingLevel loggingLevel_;
};

#endif	/* LOGGER_H */

