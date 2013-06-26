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
#include "../exceptions/filenotfoundexception.h"
#include "../exceptions/notzipfileexception.h"
#include "../exceptions/decompressexception.h"
#include "../errorcode.h"
#include "../compressor/fileheader.h"
#include "../log/LoggerManager.h"

extern LoggerManager* g_logger;
    
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
 * Decompress a file header in the output path. Throw a DecompressionException 
 * when something fails.
 * 
 * @param fileHeader File header that will be decompressed
 * @param outputPath Path of the destiny
 */
void decompressAFileHeader(const FileHeader* fileHeader, const char* outputPath) 
throw (DecompressException);

#endif	/* DECOMPRESSOR_H */

