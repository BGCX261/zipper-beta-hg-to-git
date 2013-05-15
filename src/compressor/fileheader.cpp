#include <stdlib.h>
#include <string.h>
#include "fileheader.h"

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