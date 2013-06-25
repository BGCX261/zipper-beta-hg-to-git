/* 
 * File:   FileLogger.h
 * Author: Daniela
 *
 * Created on March 21, 2013, 6:33 PM
 */

#ifndef FILELOGGER_H
#define	FILELOGGER_H

#include "Logger.h"
#include "string.h"

/**
 * Logger that logs information into a file.
 */
class FileLogger : public Logger
{
public:
    /**
     * Instantiate the logger with a open file called 'Logs.txt'.
     */
    FileLogger();

    /**
     * Instantiate the logger with a open file using the fileName param.
     * 
     * @param fileName File name
     */
    FileLogger(const char* fileName);
    FileLogger(const FileLogger& orig);
    /**
     * Close the file.
     */
    virtual ~FileLogger();

    void log(LoggingLevel level, unsigned int threadID, const char* source, char* msg);

    /**
     * Return the open log file.
     * 
     * @return Log file.
     */
    FILE* getFile() const
    {
        return file_;
    }

    /**
     * Return the log file name.
     * 
     * @return Log file name.
     */
    char* getFileName() const
    {
        return fileName_;
    }

    /**
     * Change the name of the log file. When the log file change, close the 
     * first file and open the file with the given name.
     * 
     * @param fileName Log file name
     */
    void setFileName(char* fileName)
    {
        freeFilename();
        this->fileName_ = new char[strlen(fileName) + 1];
        strcpy(this->fileName_, fileName);
        fclose(file_);
        this->file_ = fopen(fileName, "a+");
    }
private:

    void freeFilename();
    
    /**
     * Name of the log file.
     */
    char* fileName_;
    
    /**
     * File where the file logging will be done.
     */
    FILE* file_;

};

#endif	/* FILELOGGER_H */

