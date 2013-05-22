/* 
 * File:   fileutils.h
 * Author: Daniela Meneses
 * Description: This file will provide some useful functions to manage files.
 *
 * Created on May 15, 2013, 3:02 PM
 */

#ifndef FILEUTILS_H
#define	FILEUTILS_H

#include <iostream>

/**
 * Check if the file in the given path is a file. If the path doesn't exist return false.
 * 
 * @param path Path to find out if is a file.
 *
 * @return true if the file in the given path is a true file, false in other case.
 */
bool isFile(const char* path);

/**
 * Check if the file in the given path is a directory. If the path doesn't exist return false.
 * 
 * @param path Path to find out if is a directory.
 * 
 * @return true if the file in the given path is a directory, false in other case.
 */
bool isDirectory(const char* path);

/**
 * Check if the file or directory in the given path exist.
 * 
 * @param path Path to check.
 * 
 * @return true if the file or directory exist, false in other case.
 */
bool exist(const char* path);

    /**
     * Recover the last modification date and time of a file. If is directory
     * return null.
     * 
     * @param path Path of the file
     * 
     * @return A time struct with the last modification date and time
     */
    tm* recoverLastModificationDateAndTime(const char* path);

#endif	/* FILEUTILS_H */

