/* 
 * File:   fileutils.h
 * Author: Daniela Meneses
 * Description: This file will provide some useful functions to manage files.
 *
 * Created on May 15, 2013, 3:02 PM
 */

#ifndef FILEUTILS_H
#define	FILEUTILS_H
#include <list>
#include "path.h"
#include "openfileexception.h"
#include "filenotfoundexception.h"
#include "nullpathexception.h"

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
 * Get all the files recursively from the directories in the list of given paths. If some path in 
 * in the list of path is a file just adds it to the result list.
 * 
 * @param paths Contain paths of files or directories.
 * @param pathsCount Size of the given list of paths.
 * 
 * @return List that will contain all the files and directories inside the given path in order
 * of appearance.
 */
std::list<Path>* explorePaths(const char** paths, int pathsCount) throw (FileException);

#endif	/* FILEUTILS_H */

