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

using namespace std;

class ZipBuilder {
public:
    ZipBuilder();
    ZipBuilder(char** input, int inputSize);
    ZipBuilder(const ZipBuilder& other);
    ~ZipBuilder();
    void buildZipFile(ostream outputStream);

private:
    void buildFileHeaders();
    void buildCentralDirectory(FileHeader* fileHeader);
    void buildEndOfCentralDirectory(int fHeaderCount);

    list<FileHeader>* fileHeaders;
    list<Path>* inputPaths;

};


#endif	/* ZIPBUILDER_H */

