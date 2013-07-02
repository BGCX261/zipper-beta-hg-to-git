/* 
 * File:   LoggerManager.cpp
 * Author: Daniela
 * 
 * Created on March 21, 2013, 6:04 PM
 */
#include <pthread.h>
#include "LoggerManager.h"
#include "stdlib.h"

LoggerManager* g_logger = new LoggerManager();

LoggerManager::LoggerManager()
{
    this->size_ = 0;
    this->capacity_ = 2;
    this->loggers_ = (Logger**) calloc(capacity_, sizeof (Logger*));
    this->bufferSize_ = BUFFER_GROW_SIZE;
    this->buffer_ = new char[bufferSize_];
}

LoggerManager::LoggerManager(const LoggerManager& orig)
{
}

LoggerManager::~LoggerManager()
{
    for (int i = 0; i < size_; i++)
    {
        delete loggers_[i];
    }

    free(loggers_);
    freeBuffer();
}

void LoggerManager::log(LoggingLevel level, const char* source, const char* format, ...)
{
    int res = -1;
    unsigned int threadID = (unsigned int) pthread_self();
    bool bufferLoaded = false;

    while (!bufferLoaded)
    {
        va_list args;
        va_start(args, format);
        res = vsnprintf(buffer_, bufferSize_, format, args);
        va_end(args);

        if (res < bufferSize_ && res >= 0)
        {
            bufferLoaded = true;
        }
        else
        {
            resizeBuffer();
        }
    }

    for (int i = 0; i < size_; i++)
    {
        loggers_[i]->log(level, threadID, source, buffer_);
    }
}

bool LoggerManager::addFileLogger(const char* filename)
{
    if (!filename) return false;
    if (size_ == capacity_) return false; //Maybe gonna be resized.
    loggers_[size_] = new FileLogger(filename);
    size_++;
    return true;
}

void LoggerManager::freeBuffer()
{
    if (this->buffer_)
    {
        delete[] this->buffer_;
        this->buffer_ = 0;
    }
}

void LoggerManager::resizeBuffer()
{
    freeBuffer();
    this->bufferSize_ *= 2;
    this->buffer_ = new char[bufferSize_];
}

