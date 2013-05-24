#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "fileheader.h"
#include "../utils/crc32.h"
#include "../utils/fileutils.h"
#include "../utils/zipperutils.h"

#define FILE_HEADER_SIGNATURE  0x04034b50

using namespace std;

FileHeader::FileHeader():extraField(0), data(0) 
{
    initialize();
}

FileHeader::FileHeader(const FileHeader& other) : extraField(0), data(0) 
{
    initialize(other);
}

FileHeader& FileHeader::operator =(const FileHeader& other) 
{
    if (&other != this) 
    {
        release();
        initialize(other);
    }

    return *this;
}

FileHeader::~FileHeader() 
{
    release();
}

bool FileHeader::operator ==(const FileHeader& other) 
{
    return fileName == other.fileName;
}

void FileHeader::setExtraField(const char* extraField, const size_t extraFieldLength) 
{
    if (this->extraField) 
    {
        free(this->extraField);
        this->extraField = 0;
    }

    if (extraField) 
    {
        this->extraFieldLength = extraFieldLength;
        this->extraField = (char*) malloc(extraFieldLength);
        memcpy(this->extraField, extraField, extraFieldLength);
    }
}

void FileHeader::setData(const char* data, const size_t dataLength)
{
    if (this->data) 
    {
        free(this->data);
        this->data = 0;
    }
    
    if(data)
    {
        dataSize = dataLength;
        this->data = (char*) malloc(dataSize);
        memcpy(this->data, data, dataSize);
    }
}

int FileHeader::size()
{
    return 30 + fileNameLength + extraFieldLength + dataSize;
}

bool FileHeader::compare(const FileHeader& other)
{
    return  headerSignature == other.headerSignature &&
            versionToExtract == other.versionToExtract &&
            flag == other.flag &&
            compressionMethod == other.compressionMethod &&
            lastModificationTime == other.lastModificationTime &&
            lastModificationDate == other.lastModificationDate &&
            crc == other.crc &&
            compressedSize == other.compressedSize &&
            unCompressedSize == other.unCompressedSize &&
            fileNameLength == other.fileNameLength &&
            extraFieldLength == other.extraFieldLength &&
            fileName == other.fileName &&
            memcmp(extraField, other.extraField, extraFieldLength) == 0 &&
            memcmp(data, other.data, dataSize) == 0;
}

void FileHeader::initialize(const FileHeader& other)
{
    headerSignature = other.headerSignature;
    versionToExtract = other.versionToExtract;
    flag = other.flag;
    compressionMethod = other.compressionMethod;
    lastModificationTime = other.lastModificationTime;
    lastModificationDate = other.lastModificationDate;
    crc = other.crc;
    compressedSize = other.compressedSize;
    unCompressedSize = other.compressedSize;
    fileNameLength = other.fileNameLength;
    fileName = other.fileName;
    setExtraField(other.extraField, other.extraFieldLength);
    setData(other.data, other.dataSize);
}

void FileHeader::initialize()
{
    headerSignature = FILE_HEADER_SIGNATURE;
    versionToExtract = 0;
    flag = 0;
    compressionMethod = 0;
    lastModificationTime = 0;
    lastModificationDate = 0;
    crc = 0;
    compressedSize = 0;
    unCompressedSize = 0;
    fileNameLength = 0;
    extraFieldLength = 0;
    extraField = 0;
    data = 0;
    dataSize = 0;
}

void FileHeader::release() 
{
    if (data) 
    {
        free(data);
        data = 0;
    }

    if (extraField) 
    {
        free(extraField);
        extraField = 0;
    }
}

FileHeader* createFileHeader(const Path* path, const short compressionMethod)
{    
    if(!path)
    {
        return NULL;
    }
    
    FILE* file = fopen(path->fullPath.c_str(), "rb");
    int dataSize = 0;
    char* data = 0;
    
    if(isFile(path->fullPath.c_str()))
    {
        fseek(file, 0, SEEK_END);
        dataSize = ftell(file);
        fseek(file, 0, SEEK_SET);
    }
    
    data = (char*) malloc(dataSize);
    fread(data, sizeof(char), dataSize, file);
    tm* time = recoverLastModificationDateAndTime(path->fullPath.c_str());
    
    FileHeader* header = new FileHeader();
    header->versionToExtract = 10;
    header->flag = 0;
    header->compressionMethod = compressionMethod;
    header->lastModificationTime = parseTimeToMSDosFormat(time);
    header->lastModificationDate = parseDateToMSDosFormat(time);
    header->crc = crc32(data, dataSize);
    header->unCompressedSize = dataSize;
    header->fileNameLength = path->relativePath.length();
    header->extraFieldLength = 0;
    header->fileName = path->relativePath;
    
    switch (compressionMethod)
    {
        case 0: header->compressedSize = dataSize;
                header->setData(data, dataSize);
            break;
        case 8: header->compressedSize = dataSize;
                header->setData(data, dataSize);
            break; 
    }
    
    free(data);
    fclose(file);
    return header;
}

void getBuffer(FileHeader* fh, char*& buffer)
{
    if(!fh)
    {
        buffer = NULL;
    }
    else
    {
        buffer = (char*) malloc(fh->size());
        memcpy(buffer + 0, &fh->headerSignature, 4);
        memcpy(buffer + 4, &fh->versionToExtract, 2);
        memcpy(buffer + 6, &fh->flag, 2);
        memcpy(buffer + 8, &fh->compressionMethod, 2);
        memcpy(buffer + 10, &fh->lastModificationTime, 2);
        memcpy(buffer + 12, &fh->lastModificationDate, 2);
        memcpy(buffer + 14, &fh->crc, 4);
        memcpy(buffer + 18, &fh->compressedSize, 4);
        memcpy(buffer + 22, &fh->unCompressedSize, 4);
        memcpy(buffer + 26, &fh->fileNameLength, 2);
        memcpy(buffer + 28, &fh->extraFieldLength, 2);
        memcpy(buffer + 30, fh->fileName.c_str(), fh->fileNameLength);
        memcpy(buffer + 30 + fh->fileNameLength, fh->extraField, 
                fh->extraFieldLength);
        memcpy(buffer + 30 + fh->fileNameLength + fh->extraFieldLength, 
                fh->data, fh->dataSize);
    }
}
