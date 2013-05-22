/* 
 * File:   path.h
 * Author: Daniela Meneses
 * Description: File to create a Path structure to manage files easily.
 *
 * Created on May 15, 2013, 3:22 PM
 */

#ifndef PATH_H
#define	PATH_H
#include <string>

/**
 * Structure to manage absolute and relative path of a file.
 */
struct Path
{
    /**
     * Absolute path of a file.
     */
    std::string fullPath;
    
    /**
     * Relative path of a file.
     */
    std::string relativePath;

    /**
     * Path structure constructor.
     * 
     * @param fullPath Absolute path.
     * @param relativePath Relative Path.
     */
    Path(std::string fullPath, std::string relativePath) : fullPath(fullPath), relativePath(relativePath){}
};

#endif	/* PATH_H */

