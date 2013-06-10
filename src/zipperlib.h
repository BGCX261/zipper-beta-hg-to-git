/*  
 * File:   zipperlib.h
 * Author: Daniela Meneses
 * Description: Contains the features that the Zipper library will provide to manage the compression tasks.
 * Works as a interface for the library.
 *
 * Created on May 13, 2013, 4:45 PM
 */

#ifndef ZIPPERLIB_H
#define	ZIPPERLIB_H
#include "errorcode.h"
#include "compressor/zipbuilder.h"
#include "utils/fileutils.h"
#include <fstream>

/**
 * Compress the received list of files/directories in a zip file with the selected compression 
 * method in the selected output folder.
 * 
 * @param targetPath Output where the compressed zip file is created.
 * @param inputfilePaths List of files or directories that will be compressed.
 * @param pathCount Size of the list of file or directories.
 * @param compressionMethod Selected compression method.
 * 
 * @return An error code that will explain the compression result. If the compression task is 
 *         successfull will return OK.
 */
ErrorCode compress(char* targetPath, char** inputfilePaths, int pathCount, int compressionMethod);

/**
 * Traverse a zip file showing all the containing files inside.
 * 
 * @param zipPath Zip file to navigate.
 * @param level Tell when to stop the traverse task in a tree..
 * 
 * @return An error code that will explain the navigation result. If the navigation task is 
 *         successful will return OK.
 */
ErrorCode traverse(const char* zipPath, int level);

#endif	/* ZIPPERLIB_H */
