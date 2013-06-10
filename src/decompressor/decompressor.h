/* 
 * File:   decompressor.h
 * Author: Luis Aguirre
 * Description: This file provide functions to decompress a zip file
 *
 * Created on june 4, 2013, 05:42 PM
 */

#ifndef DECOMPRESSOR_H
#define	DECOMPRESSOR_H

#include <list>
#include "../utils/filenotfoundexception.h"
#include "../exceptions/notzipfileexception.h"
#include "../errorcode.h"
#include "../compressor/fileheader.h"
    
/**
 * Collect the file headers of a zip file. If the file does not exists throws a 
 * FileNotFounException, if the given file is not a zip file throws a NotZipFileException
 * 
 * @param path Path of the zip file 
 * 
 * @return Return a file headers list
 */
std::list<FileHeader*>& navigate(const char* path) throw (FileException);

/**
 * Given a zip file decompress the zip in the output path
 * 
 * @param zipPath Path of the zip file
 * @param outputPath Path of the destiny
 * 
 * @return An Error code if some fail else return ok
 */
ErrorCode decompress(const char* zipPath, const char* outputPath);

#endif	/* DECOMPRESSOR_H */

