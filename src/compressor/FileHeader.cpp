#include <stdlib.h>
#include <string.h>
#include "FileHeader.h"

#define FILE_HEADER_SIGNATURE  0x04034b50

using namespace std;

FileHeader::FileHeader():extraField(0), data(0) {
    
    headerSignature = FILE_HEADER_SIGNATURE;
}

FileHeader::FileHeader(const FileHeader& other) : extraField(0), data(0) {
    initialize(other);
}

FileHeader& FileHeader::operator =(const FileHeader& other) {
    if (&other != this) {
        release();
        initialize(other);
    }

    return *this;
}

FileHeader::~FileHeader() {
    release();
}

bool FileHeader::operator ==(const FileHeader& other) {
    return fileName == other.fileName;
}

void FileHeader::setExtraField(const char* extraField, const size_t extraFieldLength) {
    if (this->extraField) {
        free(this->extraField);
        this->extraField = 0;
    }

    if (extraField) {
        this->extraFieldLength = extraFieldLength;
        this->extraField = (char*) malloc(extraFieldLength);
        memcpy(this->extraField, extraField, extraFieldLength);
    }
}

void FileHeader::setData(const char* data, const size_t dataLength) {
    if (this->data) {
        free(this->data);
        this->data = 0;
    }
    
    if(data)
    {
    fileDataLength = dataLength;
    this->data = (char*) malloc(fileDataLength);
    memcpy(this->data, data, fileDataLength);
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
    setData(other.data, other.fileDataLength);
}

void FileHeader::release() {
    if (data) {
        free(data);
        data = 0;
    }

    if (extraField) {
        free(extraField);
        extraField = 0;
    }
}
