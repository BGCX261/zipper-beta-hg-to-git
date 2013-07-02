/* 
 * File:   LoggerManager.h
 * Author: Daniela
 *
 * Created on March 21, 2013, 6:04 PM
 */

#ifndef LOGGERMANAGER_H
#define	LOGGERMANAGER_H
#include "Logger.h"
#include "FileLogger.h"

#define DEBUG(format, ...){g_logger->log(DEBUG, __PRETTY_FUNCTION__, format, __VA_ARGS__);}
#define INFO(format, ...){g_logger->log(INFO, __PRETTY_FUNCTION__, format, __VA_ARGS__);}
#define WARN(format, ...){g_logger->log(WARN, __PRETTY_FUNCTION__, format, __VA_ARGS__);}
#define ERROR(format, ...){g_logger->log(ERROR, __PRETTY_FUNCTION__, format, __VA_ARGS__);}
#define BUFFER_GROW_SIZE 128

/**
 * Class in charge of manage the enabled loggers.
 */
class LoggerManager
{
public:
    /**
     * Instantiate a logger manager that supports 2 loggers.
     */
    LoggerManager();

    LoggerManager(const LoggerManager& orig);

    /**
     * Free the memory used for the logger list.
     */
    virtual ~LoggerManager();

    /**
     * Perform the log action in the enabled loggers.
     * 
     * @param level Logging level
     * @param format Format for the message to log
     * @param ... Data to format the message
     */
    void log(LoggingLevel level, const char* source, const char* format, ...);

    /**
     * Create a logger and add it to the logger list for the manager.
     * 
     * @param filename Name of the file.
     * 
     * @return True if the logger was added successfully. False in other case.
     */
    bool addFileLogger(const char* filename);

    /**
     * Return the list of enables loggers.
     * 
     * @return List of loggers
     */
    Logger** getLoggers()
    {
        return loggers_;
    }

    /**
     * Get the logger count in this manager.
     * 
     * @return Loggers count.
     */
    int getLoggersCount() const
    {
        return size_;
    }

private:
    /**
     * Release memory used by the buffer.
     */
    void freeBuffer();
    /**
     * Resize the buffer size.
     */
    void resizeBuffer();

    /**
     * List of enabled loggers.
     */
    Logger** loggers_;
    /**
     * Capacity of the list.
     */
    int capacity_;
    /**
     * Loggers count.
     */
    int size_;
    /**
     * Buffer to merge pattern and varargs to pass the message to the added 
     * loggers.
     */
    char* buffer_;
    /**
     * Manage the current buffer size.
     */
    int bufferSize_;
};

#endif	/* LOGGERMANAGER_H */

