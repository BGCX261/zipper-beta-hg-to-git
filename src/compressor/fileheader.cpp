#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "fileheader.h"
#include "../utils/crc32.h"
#include "../utils/fileutils.h"
#include "../decompressor/decompressor.h"
#include "../utils/dateconverter.h"
#include "../algorithms/algorithms.h"

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

void FileHeader::setData(const char* data, const size_t dataLength, bool allocateMemory)
{
    if (this->data)
    {
        free(this->data);
        this->data = 0;
    }

    if (data)
    {
        this->dataSize = dataLength;
        if (allocateMemory)
        {
            this->data = (char*) malloc(this->dataSize);
            memcpy(this->data, data, this->dataSize);
        } else
        {
            this->data = (char*) data;
        }
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
            uncompressedSize == other.uncompressedSize &&
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
    uncompressedSize = other.compressedSize;
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
    uncompressedSize = 0;
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
throw (UnsupportedCompressionMethod)
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
    DateConverter converter;
    FileHeader* header = new FileHeader();
    header->versionToExtract = 10;
    header->flag = 0;
    header->compressionMethod = compressionMethod;
    header->lastModificationTime = converter.parseTimeToMSDosFormat(time);
    header->lastModificationDate = converter.parseDateToMSDosFormat(time);
    header->crc = crc32(data, dataSize);
    header->uncompressedSize = dataSize;
    header->fileNameLength = path->relativePath.length();
    header->extraFieldLength = 0;
    header->fileName = path->relativePath;
    
        switch (compressionMethod)
    {
        case 0:
            header->setData(data, dataSize, false);
            header->compressedSize = dataSize;
            // header becomes responsible of releasing data buffer
            data = 0; 
            break;
        case 12:
        {
            DataInfo dataInfo = bz2Compression(data, dataSize);
            header->compressedSize = dataInfo.length;
            header->setData(dataInfo.data, dataInfo.length, false);
            break;
        }
        default:
            throw UnsupportedCompressionMethod(compressionMethod, UNSUPPORTED_COMPRESSION);
    }
    if (data)
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
        memcpy(buffer + 22, &fh->uncompressedSize, 4);
        memcpy(buffer + 26, &fh->fileNameLength, 2);
        memcpy(buffer + 28, &fh->extraFieldLength, 2);
        memcpy(buffer + 30, fh->fileName.c_str(), fh->fileNameLength);
        memcpy(buffer + 30 + fh->fileNameLength, fh->extraField, 
                fh->extraFieldLength);
        memcpy(buffer + 30 + fh->fileNameLength + fh->extraFieldLength, 
                fh->data, fh->dataSize);
    }
}
