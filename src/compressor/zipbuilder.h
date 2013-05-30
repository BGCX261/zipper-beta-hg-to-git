/* 
 * File:   zipbuilder.h
 * Author: Kenji
 * Description: The builder of the zip file
 *
 */

#ifndef ZIPBUILDER_H
#define	ZIPBUILDER_H

#define C_DIRECTORY_PARTIAL_SIZE 46

#include "fileheader.h"
#include "../utils/path.h"
#include "../utils/fileutils.h"
#include <list>
#include <stdlib.h>
#include <sstream>
#include <string.h>


using namespace std;

class ZipBuilder
{
public:
    /**
     * Zip Builder Constructor. Create the builder of the zip file given
     * the input files or directories and the compression method. 
     * @param input The input paths.
     * @param inputSize The size of the input paths.
     * @param compresssionMethod The number of compressiom method.
     */
    ZipBuilder(char** input, int inputSize, int compresssionMethod);

    /**
     *Zip Builder Destructor.
     */
    ~ZipBuilder();

    /**
     * Build the zip file structure given an iostream
     * @param outputStream The outpustream that will store the zip file structure
     */
    void buildZipFile(iostream* outputStream);

private:
    /**
     * Zip Builder Copy Constructor.
     * @param other The reference to be copied.
     */
    ZipBuilder(const ZipBuilder& other);

    /**
     * Build the FileHeaders for the zip file
     * @param outputStream The output stream that will store the file headers
     */
    void buildFileHeaders(iostream* outputStream);

    /**
     * Build the file header
     * @param path The path of file or directory to build file header 
     * @param outputStream The output stream that will store the file header
     */
    void buildFileHeader(const Path& path, iostream* outputStream);

    /**
     * Build the central directory in the output stream given a file header
     * @param fileHeader The file header to create the central directory
     * @param outputStream The output stream that will store the central directory
     */
    void buildCentralDirectory(FileHeader* fileHeader, iostream* outputStream);

    /**
     * Build the end of cental directory
     * @param fHeaderCount The number of file headers in the zip file structure
     * @param outputStream The output stream that will store the end of central directory
     */
    void buildEndOfCentralDirectory(int fHeaderCount, iostream* outputStream);

    /**
     * Delete the List of FileHeaders
     */
    void deleteFileHeaders();
    
    list<FileHeader*>* fileHeaders_;
    
    list<Path>* inputPaths_;
    
    int compressionMethod_;
    
    int currentOffset_;
    
    int cDirectoryOffset_;
};


#endif	/* ZIPBUILDER_H */

