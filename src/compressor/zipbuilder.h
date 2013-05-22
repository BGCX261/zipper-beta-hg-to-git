/* 
 * File:   zipbuilder.h
 * Author: Kenji
 * Description: The builder of the zip file
 *
 */

#ifndef ZIPBUILDER_H
#define	ZIPBUILDER_H

#include "fileheader.h"
#include <list>

using namespace std;
        
class ZipBuilder
{
public:
    ZipBuilder();
    ZipBuilder(const ZipBuilder& other);
    ~ZipBuilder();
    void addFile(PATH path);
    char* getZipStructure();
private:
    void buildCentralDirectory(FileHeader fileHeader);
    void buildEndOfCentralDirectory(int fHeaderCount, int offsetCDirectory);
    
    list<FileHeader> fileHeaders;
    char* buffer;
    int cDirectoryOffset;
    int endOfCDirectoryOffset;
    int bufferSize;


};


#endif	/* ZIPBUILDER_H */

