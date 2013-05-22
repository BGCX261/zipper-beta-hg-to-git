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
     * Path structure constructor. Just set the values.
     * 
     * @param fullPath Absolute path.
     * @param relativePath Relative Path.
     */
    Path(std::string fullPath, std::string relativePath) : fullPath(fullPath), relativePath(relativePath)
    {
    }

    /**
     * Path structure constructor. Set the values and add a (/) in the relative path when is a directory.
     * 
     * @param fullPath Absolute path.
     * @param relativePath Relative Path.
     * @param isDir Tells when the path owner is a file or directory.
     */
    Path(std::string fullPath, std::string relativePath, bool isDir) : fullPath(fullPath), relativePath(relativePath)
    {
        if (isDir)
        {
            this->relativePath.append("/");
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
    Path(std::string fullPath, std::string relativePath, std::string filename, bool isDir)
    {
        this->fullPath = fullPath;
        this->fullPath.append("/");
        this->fullPath.append(filename);
        this->relativePath = relativePath;
        this->relativePath.append(filename);

        if (isDir)
        {
            this->relativePath.append("/");
        }
    }
};

#endif	/* PATH_H */

