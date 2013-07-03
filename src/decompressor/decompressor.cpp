#include "decompressor.h"
#include "../utils/fileutils.h"
#include <list>
#include "../compressor/fileheader.h"
#include "../utils/dateconverter.h"
#include "../exceptions/unsupportedcompressionmethod.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

void navigate(const char* path, std::list<FileHeader*>& fileHeaders) throw (FileException)
{
    INFO("Navigating a zip file in the path: %s", path);
    int signature;
    const char* zipExtension = ".zip";
    FILE* file = fopen(path, "rb");

    if (!path)
    {
        WARN("%s", "The path is NULL.");
        throw NullPathException(INVALID_PARAMETERS);
    }

    if (!exist(path))
    {
        WARN("%s", "The path doesn't exist.")
        throw FileNotFoundExpcetion(path, FILE_NOT_FOUND);
    }

    fread(&signature, sizeof (int), 1, file);

    if (strlen(path) < 4 || strcmp(path + (strlen(path) - 4), zipExtension) != 0 ||
            signature != FILE_HEADER_SIGNATURE)
    {
        WARN("%s", "The path isn't for a zip file.")
        throw NotZipFileException(path, INVALID_ZIP_FILE);
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

            fileHeaders.push_back(fh);
        }

        fread(&signature, sizeof (int), 1, file);
    }
}


void decompressAFileHeader(const FileHeader* fileHeader, const char* outputPath) 
throw(DecompressException)
{
    if(!fileHeader)
    {
        WARN("%s", "The file header is NULL");
        throw DecompressException("FileHeader NULL", DECOMPRESS_FAIL);
    }
    
    INFO("Decompressing this file header: %s", fileHeader->fileName.c_str());
    DateConverter converter;
    int outputSize = strlen(outputPath);
    char* name = (char*) malloc(outputSize + fileHeader->fileNameLength + 2);
    memset(name, 0, outputSize + fileHeader->fileNameLength + 2);
    memcpy(name, outputPath, outputSize); //TODO Sprintf
    memcpy(name + outputSize, "/", 1);
    memcpy(name + outputSize + 1, fileHeader->fileName.c_str(), 
            fileHeader->fileNameLength);
    bool isDirectory = name[strlen(name) - 1] == '/';
    if(isDirectory)
    {
        if(!createADirectory(name))
        {
            WARN("%s", "The directory can't be created.");
            string message = "Cannot create the directory: ";
            message.append(name);
            throw DecompressException(message.c_str(), DECOMPRESS_FAIL);
        }
    }
    else
    {
        FILE* file = fopen(name, "wb");
        if (file == NULL)
        {
            WARN("%s", "The file can't be created.");
            string message = "Cannot create the file: ";
            message.append(name);
            throw DecompressException(message.c_str(), DECOMPRESS_FAIL);
        }
        switch(fileHeader->compressionMethod)
        {
            case 0:
                fwrite(fileHeader->data, sizeof(char), fileHeader->dataSize, file);
                fclose(file);
                break;
            default:
                fclose(file);
                throw UnsupportedCompressionMethod(fileHeader->compressionMethod, UNSUPPORTED_COMPRESSION);
        }
        
        tm* date = converter.parseMSDosToTm(fileHeader->lastModificationDate, 
                fileHeader->lastModificationTime);
        setLastModificationDateAndTime(name, date);
    }
    free(name);
}
