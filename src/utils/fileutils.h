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

/**
 * Recover the last modification date and time of a file. If is directory
 * return null.
 * 
 * @param path Path of the file
 * 
 * @return A time struct with the last modification date and time
 */
tm* recoverLastModificationDateAndTime(const char* path);

/**
 * Check the if the target path contains a name of zip file.
 * If target path does not contain a valid name, it uses the firstFileName
 * to create a valid name of zip file
 * 
 * @param targetPath The target path to check if is a valid name
 * @param firsFileName The file name to create zip file name if the target path is not correct
 * 
 * @return The name to create a zip file 
 */
std::string prepareTargetPath(const char* targetPath, const char* firsFileName);    

/**
 * Get the file name inside a given path. 
 * For example: If the path is /folder1/file1.txt it will return file1.txt.
 * Always will search the last slash in the path.
 * 
 * @param path Path to get the filename.
 * 
 * @return The filename, if is not found will return the given path.
 */
std::string getFileName(const std::string path);
#endif	/* FILEUTILS_H */

