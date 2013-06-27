/* 
 * File:   FileLogger.cpp
 * Author: Daniela
 * 
 * Created on March 21, 2013, 6:33 PM
 */

#include "FileLogger.h"

FileLogger::FileLogger(const char* fileName)
{
    this->fileName_ = new char[strlen(fileName) + 1];
    strcpy(this->fileName_, fileName);
    this->loggingLevel_ = INFO;
    this->file_ = fopen(fileName, "a+");
}

FileLogger::FileLogger(const FileLogger& orig)
{
}

FileLogger::~FileLogger()
{
    freeFilename();
    fclose(file_);
    file_ = 0;
}

void FileLogger::log(LoggingLevel level, unsigned int threadID, const char* source, char* msg)
{
    if (file_ == NULL) return;
    if (level <= loggingLevel_ && this->file_)
    {
        const char* time = getCurrentTime();
        const char* levelStr = loggingLevelToString(level);
        fprintf(this->file_, "%s [%u] [%s] %s: %s\n", time, threadID, source, levelStr, msg);
    }
}

void FileLogger::freeFilename()
{
    if (this->fileName_)
    {
        delete[] this->fileName_;
        this->fileName_ = 0;
    }
}

