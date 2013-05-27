#include "zipbuilder.h"

ZipBuilder::ZipBuilder(char** input, int inputSize, int compressionMethod) {
    this->inputPaths = explorePaths((const char**) input, inputSize);
    this->fileHeaders = new list<FileHeader*>();
    this->compressionMethod = compressionMethod;
}

ZipBuilder::ZipBuilder(const ZipBuilder& other) {
    this->inputPaths = other.inputPaths;
    this->fileHeaders = other.fileHeaders;
    this->compressionMethod = other.compressionMethod;
}

ZipBuilder::~ZipBuilder() {
    if (this->fileHeaders)
        //TO-DO: free the file headers
        delete fileHeaders;
    if (this->inputPaths)
        delete inputPaths;
}

void ZipBuilder::buildZipFile(iostream* outputStream) {
    buildFileHeaders(outputStream);
    list<FileHeader*>::iterator fHeaderIterator;
    for (fHeaderIterator = fileHeaders->begin(); fHeaderIterator != fileHeaders->end(); fHeaderIterator++) {
        FileHeader* fileHeader = *fHeaderIterator;
        buildCentralDirectory(fileHeader, outputStream);
    }
    buildEndOfCentralDirectory(fileHeaders->size(), outputStream);
}

void ZipBuilder::buildFileHeaders(iostream* outputStream) {
    FileHeader* fileHeader = 0;
    int currentOffset = 0;
    int currentSize = 0;

    list<Path>::iterator pathIterator;

    for (pathIterator = inputPaths->begin(); pathIterator != inputPaths->end(); pathIterator++) {
        fileHeader = buildFileHeader(*pathIterator, outputStream);
        currentSize = fileHeader->size();
        fileHeader->offset = currentOffset;
        currentOffset += currentSize;
        this->fileHeaders->push_back(fileHeader);
    }
}

FileHeader* ZipBuilder::buildFileHeader(const Path& path, iostream* outputStream) {
    FileHeader* fileHeader = 0;
    char* buffer = 0;
    fileHeader = createFileHeader(&path, compressionMethod);
    buffer = new char[fileHeader->size()];

    getBuffer(fileHeader, buffer);
    outputStream->write(buffer, fileHeader->size());

    delete[] buffer;
}

void ZipBuilder::buildCentralDirectory(FileHeader* fileHeader, iostream* outputStream) {

    int buffersize = C_DIRECTORY_PARTIAL_SIZE + fileHeader->fileNameLength;
    char* buffer = new char[buffersize];
    int signature = 0x02014b50;
    short version = 31;
    short commentLength = 0;
    short diskStart = 0;
    short internalAttribute = 0;
    int externalAtribute = 0;
    memcpy(buffer, &signature, 4);
    memcpy(buffer, &version, 2);
    memcpy(buffer, &fileHeader->versionToExtract, 2);
    memcpy(buffer, &fileHeader->flag, 2);
    memcpy(buffer, &fileHeader->compressionMethod, 2);
    memcpy(buffer, &fileHeader->lastModificationTime, 2);
    memcpy(buffer, &fileHeader->lastModificationDate, 2);
    memcpy(buffer, &fileHeader->crc, 4);
    memcpy(buffer, &fileHeader->compressedSize, 4);
    memcpy(buffer, &fileHeader->unCompressedSize, 4);
    memcpy(buffer, &fileHeader->fileNameLength, 2);
    memcpy(buffer, &fileHeader->extraFieldLength, 2);
    memcpy(buffer, &commentLength, 2);
    memcpy(buffer, &diskStart, 2);
    memcpy(buffer, &internalAttribute, 2);
    memcpy(buffer, &externalAtribute, 4);
    memcpy(buffer, &fileHeader->offset, 4);
    memcpy(buffer, &fileHeader->fileName, fileHeader->fileNameLength);
    memcpy(buffer, &fileHeader->extraField, fileHeader->extraFieldLength);

    outputStream->write(buffer, buffersize);

    delete[] buffer;
}

void ZipBuilder::buildEndOfCentralDirectory(int fHeaderCount, iostream* outputStream) {

}


