/* 
 * File:   unsupportedcompressionmethod.h
 * Author: Luis Aguirre
 * Description: Provide an exception when the compression method is unsupported or it is unknown.
 *
 * Created on june 12, 2013, 03:14 PM
 */

#ifndef UNSUPPORTEDCOMPRESSIONMETHOD_H
#define	UNSUPPORTEDCOMPRESSIONMETHOD_H

#include "decompressexception.h"
#include <string>
#include <sstream>

#define NON_COMPRESION_METHOD ": Non Compression Method"
#define DEFLATE ": Deflate"
#define UNKNOWN_COMPRESSION_METHOD ": Unknown compression method"

/**
 * @param compressionMethod
 */
class UnsupportedCompressionMethod : public DecompressException
{
public:
        
    /**
     * Initialize the message exception.
     * 
     * @param file path of the file
     */
    UnsupportedCompressionMethod(const int compressionMethod, ErrorCode error) 
             : DecompressException("Unsupported Compression Method", error)
    {
        std::stringstream stream;
        stream << compressionMethod;
        message_ = "Unsupported compression method: ";
        message_.append(stream.str());
        message_.append(compressionMethodToString(compressionMethod));
        message_.append(".");
    }
    
    virtual ~UnsupportedCompressionMethod() throw(){}
    
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
    
    /**
     * Return the name of the compression method.
     * 
     * @param compressionMethod Compression method
     * 
     * @return The name of the compressionMethod
     */
    const char* compressionMethodToString(int compressionMethod)
    {
        switch(compressionMethod)
        {
            case 0:
                return NON_COMPRESION_METHOD;
            case 8:
                return DEFLATE;
        }
        
        return UNKNOWN_COMPRESSION_METHOD;
    }
};


#endif	/* UNSUPPORTEDCOMPRESSIONMETHOD_H */

