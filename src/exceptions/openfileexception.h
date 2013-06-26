/* 
 * File:   OpenFileException.h
 * Author: Daniela Meneses
 * Description: Define a file exception.
 *
 * Created on May 23, 2013, 6:30 PM
 */

#ifndef OPENFILEEXCEPTION_H
#define	OPENFILEEXCEPTION_H
#include "fileexception.h"


/**
 * Exception that will be thrown when a file can't be open.
 */
class OpenFileException : public FileException
{
public:

    OpenFileException(const char* file, ErrorCode error) : FileException(error)
    {
        message_ = "File can't be open: ";
        message_.append(file);
        message_.append(".");
    }
    
    virtual ~OpenFileException() throw(){}

    /**
     * Describe the general cause of the current error. 
     * 
     * @return String with the error.
     */
    virtual const char* what() const throw ()
    {
        return message_.c_str();
    }
private:
    /**
     * Message containing the error.
     */
    std::string message_;
};

#endif	/* OPENFILEEXCEPTION_H */

