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
#include <list>

using namespace std;

class ZipBuilder {
public:
    ZipBuilder();
    ZipBuilder(const ZipBuilder& other);
    ~ZipBuilder();
    void addFile(Path path);
    char* getZipStructure();
    int zipFileSize();

private:
    void conCat(char* buffer, const char* toCopy, size_t since, const size_t size);
    void buildFileHeaders();
    void buildCentralDirectory(FileHeader* fileHeader);
    void buildEndOfCentralDirectory(int fHeaderCount);
    
    list<FileHeader> fileHeaders;
    char* buffer;
    int currentOffset;
    int cDirectoryOffset;
    int endOfCDirectoryOffset;
    int bufferSize;


};


#endif	/* ZIPBUILDER_H */

