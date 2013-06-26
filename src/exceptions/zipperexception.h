/* 
 * File:   zipperexception.h
 * Author: Luis Aguirre
 * Description: Exception parent that contains an error code
 *
 * Created on june 26, 2013, 03:43 PM
 */

#ifndef ZIPPEREXCEPTION_H
#define	ZIPPEREXCEPTION_H

#include <exception>
#include "../errorcode.h"

class ZipperException : public std::exception
{
public:
        
    ZipperException(ErrorCode errorCode) : error_(errorCode)
    {
    }
    
    /**
     * Describe the general cause of the current error. 
     * 
     * @return String with the error.
     */
    virtual const char* what() const throw ()
    {
        return "Zipper exception.";
    }
    
    ErrorCode getErrorCode()
    {
        return error_;
    }
    
private:
    
    ErrorCode error_;
        
};

#endif	/* ZIPPEREXCEPTION_H */

