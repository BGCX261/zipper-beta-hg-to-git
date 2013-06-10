#include "decompressor.h"
#include "../utils/fileutils.h"
#include <list>
#include "../compressor/fileheader.h"
#include "../utils/dateconverter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

std::list<FileHeader*>& navigate(const char* path) throw (FileException)
{
    list<FileHeader*>* fileHeaders = new list<FileHeader*>();
    int signature;
    const char* zipExtension = ".zip";
    FILE* file = fopen(path, "rb");

    if (!path)
    {
        throw NullPathException();
    }

    if (!exist(path))
    {
        throw FileNotFoundExpcetion(path);
    }

    fread(&signature, sizeof (int), 1, file);

    if (strlen(path) < 4 || strcmp(path + (strlen(path) - 4), zipExtension) != 0 ||
            signature != FILE_HEADER_SIGNATURE)
    {
        throw NotZipFileException(path);
    }

    while (feof(file) == 0)
    {

        if (signature == FILE_HEADER_SIGNATURE)
        {
            FileHeader* fh = new FileHeader();
            fread(&fh->versionToExtract, sizeof (short), 1, file);
            fread(&fh->flag, sizeof (short), 1, file);
            fread(&fh->compressionMethod, sizeof (short), 1, file);
            fread(&fh->lastModificationTime, sizeof (short), 1, file);
            fread(&fh->lastModificationDate, sizeof (short), 1, file);
            fread(&fh->crc, sizeof (int), 1, file);
            fread(&fh->compressedSize, sizeof (int), 1, file);
            fread(&fh->uncompressedSize, sizeof (int), 1, file);
            fread(&fh->fileNameLength, sizeof (short), 1, file);
            fread(&fh->extraFieldLength, sizeof (short), 1, file);

            char* fileName = (char*) calloc(fh->fileNameLength + 1, sizeof (char));
            fileName[fh->fileNameLength] = '\0';
            fread(fileName, sizeof (char), fh->fileNameLength, file);
            fh->fileName = fileName;
            free(fileName);

            char* extraField = (char*) malloc(fh->extraFieldLength);
            fread(extraField, sizeof (char), fh->extraFieldLength, file);
            fh->setExtraField(extraField, fh->extraFieldLength);
            free(extraField);

            char* data = (char*) malloc(fh->compressedSize);
            fread(data, sizeof (char), fh->compressedSize, file);
            fh->setData(data, fh->compressedSize);
            free(data);

            fileHeaders->push_back(fh);
        }

        fread(&signature, sizeof (int), 1, file);
    }

    return *fileHeaders;
}


ErrorCode decompress(const char* zipPath, const char* outputPath)
{
    if (!zipPath)
    {
        return INVALID_PARAMETERS;
    }
    if (!outputPath)
    {
        return INVALID_PARAMETERS;
    }
    
    list<FileHeader*> fileHeaders;
    
    try 
    {
        fileHeaders = navigate(zipPath);
    }
    catch(FileNotFoundExpcetion)
    {
        return FILE_NOT_FOUND;
    }
    catch(NotZipFileException)
    {
        return INVALID_PARAMETERS;
    }
    
    DateConverter* converter = new DateConverter();
    
    for (std::list<FileHeader*>::iterator it = fileHeaders.begin(); it != fileHeaders.end(); 
            it++)
    {
        FileHeader* fileHeader = *it;
        int outputSize = strlen(outputPath);
        char* name = (char*) malloc(outputSize + fileHeader->fileNameLength + 2);
        memset(name, 0, outputSize + fileHeader->fileNameLength + 2);
        memcpy(name, outputPath, outputSize);
        memcpy(name + outputSize, "/", 1);
        memcpy(name + outputSize + 1, fileHeader->fileName.c_str(), 
                fileHeader->fileNameLength);
        
        if(name[strlen(name) - 1] == '/')
        {
            createADirectory(name);
        }
        else
        {
            FILE* file = fopen(name, "wb");
            fwrite(fileHeader->data, sizeof(char), fileHeader->dataSize, file);
            fclose(file);
            tm* date = converter->parseMSDosToTm(fileHeader->lastModificationDate, 
                    fileHeader->lastModificationTime);
            setLastModificationDateAndTime(name, date);
        }
        free(name);
    }
    delete converter;
    return OK;
}
