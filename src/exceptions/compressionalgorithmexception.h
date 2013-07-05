/* 
 * File:   compressionalgorithmexception.h
 * Author: Luis Aguirre
 * Description: Provide an exception when some compression algorithm fail.
 *
 * Created on july 5, 2013, 01:29 PM
 */

#ifndef COMPRESSIONALGORITHMEXCEPTION_H
#define	COMPRESSIONALGORITHMEXCEPTION_H

#include "zipperexception.h"
#include <string>

class CompressionAlgorithmException : public ZipperException
{
public:
    CompressionAlgorithmException(const char* message) : ZipperException(COMPRESSION_ALGORITHM_ERROR)
    {
        message_.append("Compression Algorithm Exception: ");
        message_.append(message);
        message_.append(".");
    }
    
    virtual ~CompressionAlgorithmException() throw(){}
    
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
    std::string  message_;
};

#endif	/* COMPRESSIONALGORITHMSEXCEPTION_H */

