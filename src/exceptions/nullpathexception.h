/* 
 * File:   nullpathexception.h
 * Author: Daniela Meneses
 * Description: Define a file exception.
 * 
 * Created on May 16, 2013, 6:03 PM
 */

#ifndef NULLPATHEXCEPTION_H
#define	NULLPATHEXCEPTION_H
#include "fileexception.h"

/**
 * Exception that will be throw when a received path is null.
 */
class NullPathException : public FileException
{
public:
    
    NullPathException(ErrorCode error) : FileException(error)
    {
    }
    /**
     * Describe the general cause of the current error. 
     * 
     * @return String with the error.
     */
    virtual const char* what() const throw ()
    {
        return "Null path exception";
    }
};

#endif	/* NULLPATH_H */

