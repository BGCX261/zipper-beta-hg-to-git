/* 
 * File:   FileException.h
 * Author: Daniela Meneses
 * Description: Define the main file exception.
 *
 * Created on May 23, 2013, 6:12 PM
 */

#ifndef FILEEXCEPTION_H
#define	FILEEXCEPTION_H
#include <exception>
#include "zipperexception.h"

/**
 * Define a general file exception.
 */
class FileException : public ZipperException 
{
public:
    
    FileException(ErrorCode error) : ZipperException(error)
    {
    }

    /**
     * Describe the general cause of the current error. 
     * 
     * @return String with the error.
     */
    virtual const char* what() const throw ()
    {
        return "File exception.";
    }
};

#endif	/* FILEEXCEPTION_H */

