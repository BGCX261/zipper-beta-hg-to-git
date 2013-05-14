/* 
 * File:   zipperLib.h
 * Author: dann
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
 * @param output Output where the compressed zip file is created.
 * @param input List of files or directories that will be compressed.
 * @param compressionMethod Selected compression method.
 * 
 * @return An error code that will explain the compression result. If the compression task is 
 *         successfull will return OK.
 */
ErrorCode compress(char* output, char** input, int compressionMethod);

#endif	/* ZIPPERLIB_H */
