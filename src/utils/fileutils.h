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
#include <string>
#include "../exceptions/openfileexception.h"
#include "../exceptions/filenotfoundexception.h"
#include "../exceptions/nullpathexception.h"
#include "../log/LoggerManager.h"

extern LoggerManager* g_logger;
struct Path;

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
 * @param List that will contain all the files and directories collected from the given path in order
 * of appearance.
 */
void explorePaths(const char** paths, int pathsCount, std::list<Path>& collectedFiles) throw (FileException);

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
std::string getFileName(const std::string& path);

/**
 * Change the last modification time and date of the given file. If the file does not exists
 * throw a FileNotFoundException.
 * 
 * @param path Path of the file
 * @param date New last modification date and time of the file
 * 
 * @return true if the file sets the last modification time and date
 */
bool setLastModificationDateAndTime(const char* path, tm* date) throw (FileException);

/**
 * Create a directory with the following permissions:
 * read, write, execute/search by owner.
 * read and write permission by group.
 * If the directory exists return ok
 * 
 * @param path Path of the directory that will be created
 * 
 * @return If the directory was created
 */
bool createADirectory(const char* path);

#endif	/* FILEUTILS_H */

