#include "zipbuilder.h"

ZipBuilder::ZipBuilder(char** input, int inputSize, int compressionMethod) {
    this->inputPaths = explorePaths((const char**) input, inputSize);
    this->fileHeaders = new list<FileHeader>();
    this->compressionMethod = compressionMethod;
}

ZipBuilder::ZipBuilder(const ZipBuilder& other) {
    this->inputPaths = other.inputPaths;
    this->fileHeaders = other.fileHeaders;
}

ZipBuilder::~ZipBuilder() {
    if (this->fileHeaders)
        delete fileHeaders;
    if (this->inputPaths)
        delete inputPaths;
}

void ZipBuilder::buildZipFile(iostream* outputStream) {
    buildFileHeaders(outputStream);
    list<FileHeader>::iterator fHeaderIterator;
    for (fHeaderIterator = fileHeaders->begin(); fHeaderIterator != fileHeaders->end(); fHeaderIterator++) {
        buildCentralDirectory(&(*fHeaderIterator), outputStream);
    }
    buildEndOfCentralDirectory(fileHeaders->size(), outputStream);
}

void ZipBuilder::buildFileHeaders(iostream* outputStream) {
    FileHeader* fileHeader = 0;
    char* buffer = 0;
    list<Path>::iterator pathIterator;
    for (pathIterator = inputPaths->begin(); pathIterator != inputPaths->end(); pathIterator++) {
        fileHeader = createFileHeader(&(*pathIterator), compressionMethod);
        this->fileHeaders->push_back(*fileHeader);
        getBuffer(fileHeader, buffer);
        outputStream->write(buffer, fileHeader->size());
        memset(buffer, 0, fileHeader->size());
        delete fileHeader;
    }
}

void ZipBuilder::buildCentralDirectory(FileHeader* fileHeader, iostream* outputStream) {
    //TO-DO: build the central directory(dummy)
}

void ZipBuilder::buildEndOfCentralDirectory(int fHeaderCount, iostream* outputStream) {
   //TO-DO: build the end central directory(dummy)
}


