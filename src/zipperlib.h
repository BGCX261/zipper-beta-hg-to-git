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

#endif	/* ZIPPERLIB_H */
