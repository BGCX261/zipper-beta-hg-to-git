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
#include "fileutils.h"

/**
 * Directory separator for files.
 * 
 */
const std::string DIRECTORY_SEPARATOR = "/";

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
     * Tell if the path owner is a file or directory.
     */
    bool isDir;

    /**
     * Path structure constructor. Set the values and add a (/) in the relative path when is a directory.
     * 
     * @param fullPath Absolute path.
     * @param relativePath Relative Path.
     * @param isDir Tells when the path owner is a file or directory.
     */
    Path(const std::string& fullPath, bool isDir) : fullPath(fullPath), isDir(isDir)
    {
        this->relativePath = getFileName(fullPath);
        
        if (isDir)
        {
            this->relativePath.append(DIRECTORY_SEPARATOR);
        }
    }

    /**
     * Path structure constructor. Set the values, adds the filename to the fullPath and the 
     * relativePath and put a (/) at the end of the relative path if is a directory.
     * 
     * @param fullPath Absolute path.
     * @param relativePath Relative Path.
     * @param isDir Tells when the path owner is a file or directory.
     */
    Path(const Path& parent, const std::string& filename, bool isDir): isDir(isDir)
    {
        this->fullPath = parent.fullPath;
        this->fullPath.append(DIRECTORY_SEPARATOR);
        this->fullPath.append(filename);
        this->relativePath = parent.relativePath;
        this->relativePath.append(filename);

        if (isDir)
        {
            this->relativePath.append(DIRECTORY_SEPARATOR);
        }
    }
};

#endif	/* PATH_H */

