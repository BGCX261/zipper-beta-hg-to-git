#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "zipperutils.h"
#include "fileutils.h"

using namespace std;

short parseDateToMSDosFormat(tm* date)
{
    if(!date)
    {
        return 0;
    }
    
    char buffer[11];
    int year;
    int month;
    int day;
    
    strftime(buffer, 11, "%Y:%m:%d", date);
    sscanf(buffer, "%d:%d:%d", &year, &month, &day);
    
    if(year != 0)
    {
        year -= 1980; //Following the MS-Dos date standard format
    }
    
    return (short) (year << 9) | (month << 5) | day; // Store the year month and day
}

short parseTimeToMSDosFormat(tm* time)
{
    if(!time)
    {
        return 0;
    }
    
    char buffer[11];
    int hour;
    int minute;
    int second;
    
    strftime(buffer, 11, "%H:%M:%S", time);
    sscanf(buffer, "%d:%d:%d", &hour, &minute, &second);
    
    if (second != 0)
    {
        second /= 2; //Following the MS-Dos date standard format
    }
    
    return (short) (hour << 11) | (minute << 5) | second; // Store the hour minute and second
}

std::list<FileHeader*>& navigate(const char* path) throw (FileException)
{
    list<FileHeader*>* fileHeaders = new list<FileHeader*>();
    const char* zipExtension = ".zip";
    
    if (!exist(path))
    {
        throw FileNotFoundExpcetion(path);
    }
    
    if(strlen(path) < 4 || strcmp(path + (strlen(path) - 4), zipExtension) != 0)
    {
        throw NotZipFileException(path);
    }
    
    FILE* file = fopen(path, "rb");
    
    int signature;
    
    while(feof(file) == 0)
    {
        fread(&signature, sizeof(int), 1, file);
        
        if(signature == FILE_HEADER_SIGNATURE)
        {
            FileHeader* fh = new FileHeader();
            fread(&fh->versionToExtract, sizeof(short), 1, file);
            fread(&fh->flag, sizeof(short), 1, file);
            fread(&fh->compressionMethod, sizeof(short), 1, file);   
            fread(&fh->lastModificationTime, sizeof(short), 1, file);   
            fread(&fh->lastModificationDate, sizeof(short), 1, file);
            fread(&fh->crc, sizeof(int), 1, file);
            fread(&fh->compressedSize, sizeof(int), 1, file);
            fread(&fh->uncompressedSize, sizeof(int), 1, file);
            fread(&fh->fileNameLength, sizeof(short), 1, file);
            fread(&fh->extraFieldLength, sizeof(short), 1, file);
            
            char* fileName = (char*) malloc(fh->fileNameLength);
            fread(fileName, sizeof(char), fh->fileNameLength, file);
            fh->fileName = fileName;
            free(fileName);
            
            char* extraField = (char*) malloc(fh->extraFieldLength);
            fread(extraField, sizeof(char), fh->extraFieldLength, file);
            fh->setExtraField(extraField, fh->extraFieldLength);
            free(extraField);
            
            char* data = (char*) malloc(fh->compressedSize);
            fread(data, sizeof(char), fh->compressedSize, file);
            fh->setData(data, fh->compressedSize);
            free(data);
            
            fileHeaders->push_back(fh);
        }
    }
    
    return *fileHeaders;
}
