/* 
 * File:   notzipfileexception.h
 * Author: Luis Aguirre
 * Description: Define a file exception.
 *
 * Created on june 1, 2013, 01:54 PM
 */

#ifndef NOTZIPFILEEXCEPTION_H
#define	NOTZIPFILEEXCEPTION_H

#include "../utils/fileexception.h"

/**
 * Throw when the file is not a zip file.
 */
class NotZipFileException : public FileException 
{
public:
    
    /**
     * Initialize the message exception.
     * 
     * @param file path of the file
     */
    NotZipFileException(const char* file) throw () : FileException()
    {
        message_ = "File isn't a zip: ";
        message_.append(file);
        message_.append(".");
    }
    
    virtual ~NotZipFileException() throw(){}
    
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

#endif	/* NOTZIPFILEEXCEPTION_H */
