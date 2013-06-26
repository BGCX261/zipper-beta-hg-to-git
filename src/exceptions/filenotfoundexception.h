/* 
 * File:   filenotfoundexpcetion.h
 * Author: Daniela Meneses 
 * Description: Define a file exception.
 *
 * Created on May 15, 2013, 3:14 PM
 */

#ifndef FILENOTFOUNDEXPCETION_H
#define	FILENOTFOUNDEXPCETION_H
#include <exception>
#include <string>
#include "fileexception.h"

/**
 * Exception that will be thrown when a file doesn't exist. 
 */
class FileNotFoundExpcetion : public FileException
{
public:

    FileNotFoundExpcetion(const char* file) throw () : FileException()
    {
        message_ = "File not found: ";
        message_.append(file);
        message_.append(".");
    }

    virtual ~FileNotFoundExpcetion() throw(){}

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

#endif	/* FILENOTFOUNDEXPCETION_H */

