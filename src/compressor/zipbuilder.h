/* 
 * File:   zipbuilder.h
 * Author: Kenji Lozano
 * Description: The builder of the zip file
 *
 */

#ifndef ZIPBUILDER_H
#define	ZIPBUILDER_H

#include "fileheader.h"
#include "../utils/path.h"
#include "../utils/fileutils.h"
#include "../errorcode.h"
#include <list>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <string.h>
#include "../log/LoggerManager.h"

extern LoggerManager* g_logger;

#define C_DIRECTORY_PARTIAL_SIZE 46

#define CDIRECTORY_SIGNATURE 0x02014b50

#define END_CDIRECTORY_SIGNATURE 0x06054b50

#define CURRENT_VERSION 31

class ZipBuilder
{
public:
    /**
     * Zip Builder Constructor. Create the builder of the zip file given
     * the input files or directories and the compression method. 
     * 
     * @param compresssionMethod The number of compressiom method.
     */
    ZipBuilder(int compresssionMethod);

    /**
     *Zip Builder Destructor.
     */
    ~ZipBuilder();

    /**
     * Build the zip file structure given an iostream
     * 
     * @param outputStream The outpustream that will store the zip file structure
     * @param inputPaths The path to build the zip file
     */
    void buildZipFile(std::iostream* outputStream, std::list<Path>& inputPaths_);

private:
    /**
     * Zip Builder Copy Constructor.
     * 
     * @param other The reference to be copied.
     */
    ZipBuilder(const ZipBuilder& other);

    /**
     * Build the FileHeaders for the zip file
     * 
     * @param outputStream The output stream that will store the file headers
     */
    void buildFileHeaders(std::iostream* outputStream, std::list<Path> inputPaths_);

    /**
     * Build the file header
     * 
     * @param path The path of file or directory to build file header 
     * @param outputStream The output stream that will store the file header
     */
    void buildFileHeader(const Path& path, std::iostream* outputStream);

    /**
     * Build the central directory in the output stream given a file header
     * 
     * @param fileHeader The file header to create the central directory
     * @param outputStream The output stream that will store the central directory
     */
    void buildCentralDirectory(FileHeader* fileHeader, std::iostream* outputStream);

    /**
     * Build the end of cental directory
     * 
     * @param fHeaderCount The number of file headers in the zip file structure
     * @param outputStream The output stream that will store the end of central directory
     */
    void buildEndOfCentralDirectory(int fHeaderCount, std::iostream* outputStream);

    /**
     * Delete the List of FileHeaders
     */
    void deleteFileHeaders();

    std::list<FileHeader*>* fileHeaders_;

    int compressionMethod_;

    int currentOffset_;

    int cDirectoryOffset_;
};


#endif	/* ZIPBUILDER_H */

