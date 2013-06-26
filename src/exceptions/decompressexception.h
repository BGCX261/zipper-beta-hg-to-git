/* 
 * File:   decompressexception.h
 * Author: Luis Aguirre
 * Description: Provide an exception when the decompression fail
 *
 * Created on june 11, 2013, 05:00 PM
 */

#ifndef DECOMPRESSEXCEPTION_H
#define	DECOMPRESSEXCEPTION_H

#include <string>
#include "zipperexception.h"

class DecompressException : public ZipperException
{
public:
    
    /**
     * Initialize the message of the exception.
     * 
     * @param msg Type of error
     */
    DecompressException(const char* msg, ErrorCode error) : ZipperException(error)
    {
        message_ = "Decompress Exception: ";
        message_.append(msg);
        message_.append(".");
    }

    virtual ~DecompressException() throw(){}

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
    
    std::string message_;
        
};

#endif	/* DECOMPRESSEXCEPTION_H */

