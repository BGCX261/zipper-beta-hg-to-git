#include "zipbuilder.h"

ZipBuilder::ZipBuilder(char** input, int inputSize, int compressionMethod)
{
    this->inputPaths_ = explorePaths((const char**) input, inputSize);
    this->fileHeaders_ = new list<FileHeader*>();
    this->compressionMethod_ = compressionMethod;
    this->currentOffset_ = 0;
    this->cDirectoryOffset_ = 0;
}

ZipBuilder::ZipBuilder(const ZipBuilder& other)
{
    this->inputPaths_ = other.inputPaths_;
    this->fileHeaders_ = other.fileHeaders_;
    this->compressionMethod_ = other.compressionMethod_;
    this->currentOffset_ = other.currentOffset_;
    this->cDirectoryOffset_ = other.cDirectoryOffset_;
}

ZipBuilder::~ZipBuilder()
{
    if (this->fileHeaders_)
    {
        deleteFileHeaders();
        delete fileHeaders_;
    }
    if (this->inputPaths_)
        delete inputPaths_;
}

void ZipBuilder::buildZipFile(iostream* outputStream)
{
    buildFileHeaders(outputStream);
    list<FileHeader*>::iterator fHeaderIterator;
    this->cDirectoryOffset_ = currentOffset_;
    for (fHeaderIterator = fileHeaders_->begin(); fHeaderIterator != fileHeaders_->end(); fHeaderIterator++)
    {
        FileHeader* fileHeader = *fHeaderIterator;
        buildCentralDirectory(fileHeader, outputStream);
    }
    buildEndOfCentralDirectory(fileHeaders_->size(), outputStream);
}

void ZipBuilder::buildFileHeaders(iostream* outputStream)
{
    list<Path>::iterator pathIterator;

    for (pathIterator = inputPaths_->begin(); pathIterator != inputPaths_->end(); pathIterator++)
    {
        buildFileHeader(*pathIterator, outputStream);
    }
}

void ZipBuilder::buildFileHeader(const Path& path, iostream* outputStream)
{
    char* buffer = 0;
    FileHeader* fileHeader = createFileHeader(&path, compressionMethod_);
    buffer = new char[fileHeader->size()];

    fileHeader->offset = currentOffset_;
    currentOffset_ += fileHeader->size();

    getBuffer(fileHeader, buffer);
    outputStream->write(buffer, fileHeader->size());
    fileHeaders_->push_back(fileHeader);

    delete[] buffer;
}

void ZipBuilder::buildCentralDirectory(FileHeader* fileHeader, iostream* outputStream)
{
    int buffersize = C_DIRECTORY_PARTIAL_SIZE + fileHeader->fileNameLength;
    currentOffset_ += buffersize;
    char* buffer = new char[buffersize];
    int signature = 0x02014b50;
    short version = 31;
    short commentLength = 0;
    short diskStart = 0;
    short internalAttribute = 0;
    int externalAtribute = 0;
    memcpy(buffer+0, &signature, 4);
    memcpy(buffer+4, &version, 2);
    memcpy(buffer+6, &fileHeader->versionToExtract, 2);
    memcpy(buffer+8, &fileHeader->flag, 2);
    memcpy(buffer+10, &fileHeader->compressionMethod, 2);
    memcpy(buffer+12, &fileHeader->lastModificationTime, 2);
    memcpy(buffer+14, &fileHeader->lastModificationDate, 2);
    memcpy(buffer+16, &fileHeader->crc, 4);
    memcpy(buffer+20, &fileHeader->compressedSize, 4);
    memcpy(buffer+24, &fileHeader->unCompressedSize, 4);
    memcpy(buffer+28, &fileHeader->fileNameLength, 2);
    memcpy(buffer+30, &fileHeader->extraFieldLength, 2);
    memcpy(buffer+32, &commentLength, 2);
    memcpy(buffer+34, &diskStart, 2);
    memcpy(buffer+36, &internalAttribute, 2);
    memcpy(buffer+38, &externalAtribute, 4);
    memcpy(buffer+42, &fileHeader->offset, 4);
    memcpy(buffer+46, fileHeader->fileName.c_str(), fileHeader->fileNameLength);
    memcpy(buffer+46+fileHeader->fileNameLength, fileHeader->extraField, fileHeader->extraFieldLength);

    outputStream->write(buffer, buffersize);
    delete[] buffer;

}

void ZipBuilder::buildEndOfCentralDirectory(int fHeaderCount, iostream* outputStream)
{
    int cDirectorySize = (currentOffset_-cDirectoryOffset_);
    int endOfCentralDirectorySize = 22;
    int endOfCentralDirectorySignature = 0x06054b50;
    char* buffer = new char[endOfCentralDirectorySize];
    short numberOfDisk = 0;
    short centralDirectoryStart = 0;
    short cDRecords = fHeaderCount;
    short numberOfCDRecords = fHeaderCount;
    short commentLength = 0;

    memcpy(buffer+0, &endOfCentralDirectorySignature, 4);
    memcpy(buffer+4, &numberOfDisk, 2);
    memcpy(buffer+6, &centralDirectoryStart, 2);
    memcpy(buffer+8, &cDRecords, 2);
    memcpy(buffer+10, &numberOfCDRecords, 2);
    memcpy(buffer+12, &cDirectorySize, 4);
    memcpy(buffer+16, &cDirectoryOffset_, 4);
    memcpy(buffer+20, &commentLength, 2);
    outputStream->write(buffer, endOfCentralDirectorySize);
    delete[] buffer;
}

void ZipBuilder::deleteFileHeaders()
{
    list<FileHeader*>::iterator fHeaderIterator;
    for (fHeaderIterator = fileHeaders_->begin(); fHeaderIterator != fileHeaders_->end(); fHeaderIterator++)
    {
        delete (*fHeaderIterator);
    }
}


