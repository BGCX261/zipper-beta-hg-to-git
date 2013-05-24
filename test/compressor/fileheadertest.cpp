
/*
 * File:   FileHeaderTest.cpp
 * Author: Luis Aguirre
 *
 * Created on 14-may-2013, 15:54:34
 */

#include <string.h>
#include <stdlib.h>
#include "fileheadertest.h"
#include "compressor/fileheader.h"
#include "utils/path.h"


CPPUNIT_TEST_SUITE_REGISTRATION(FileHeaderTest);

FileHeader* header;

FileHeaderTest::FileHeaderTest()
{
}

FileHeaderTest::~FileHeaderTest()
{
}

void FileHeaderTest::setUp()
{
    header = new FileHeader();
}

void FileHeaderTest::tearDown()
{
    delete header;
    header = 0;
}

void FileHeaderTest::testStructure()
{

    header->fileName = "File1";
    header->versionToExtract = 10;
    header->compressionMethod = 0;
    header->flag = 10;
    header->crc = 123456;
    header->lastModificationTime = 34568;
    header->lastModificationDate = 24963;
    header->compressedSize = 12;
    header->unCompressedSize = 12;
    header->setData("", 0);
    header->setExtraField("", 0);

    FileHeader fh2 = *header;

    CPPUNIT_ASSERT(header->compare(fh2));
}

void FileHeaderTest::testSetData()
{
    const char* data = "sample data";
    const int dataLength = strlen(data);
    header->setData(data, dataLength);
    CPPUNIT_ASSERT(memcmp(data, header->data, dataLength) == 0);
}

void FileHeaderTest::testSetExtraField()
{
    const char* field = "Field to compress";
    const int extraFieldLength = strlen(field);
    header->setExtraField(field, extraFieldLength);
    CPPUNIT_ASSERT(memcmp(field, header->extraField, extraFieldLength) == 0);
}

void FileHeaderTest::testCreateFileHeaderGivenAFile()
{
    FILE* file = fopen("resources/song.mp3", "rb");
    Path* path = new Path("resources/song.mp3", "song.mp3");
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* data = (char*) malloc(size);
    fread(data, sizeof(char), size, file);
    fclose(file);
    
    FileHeader* expected = new FileHeader();
    expected->versionToExtract = 10;
    expected->flag = 0;
    expected->compressionMethod = 0;
    expected->lastModificationTime = 44363;
    expected->lastModificationDate = 17073;
    expected->crc = 0xA8436532;
    expected->compressedSize = 24691;
    expected->unCompressedSize = 24691;
    expected->fileNameLength = path->relativePath.length();
    expected->extraFieldLength = 0;
    expected->fileName = "song.mp3";
    expected->setExtraField("", 0);
    expected->setData(data, size);
    
    
    FileHeader* result = createFileHeader(path, 0);
    free(data);
    
    CPPUNIT_ASSERT(result->compare(*expected));
    
    delete path;
    delete expected;
    
}

void FileHeaderTest::testCreateFileHeaderGivenADirectory()
{    
    FileHeader* expected = new FileHeader();
    expected->versionToExtract = 10;
    expected->flag = 0;
    expected->compressionMethod = 0;
    expected->lastModificationTime = 0;
    expected->lastModificationDate = 0;
    expected->crc = 0;
    expected->compressedSize = 0;
    expected->unCompressedSize = 0;
    expected->fileNameLength = strlen("directorytest/");
    expected->extraFieldLength = 0;
    expected->fileName = "directorytest/";
    expected->setExtraField("", 0);
    expected->setData("", 0);
    
    Path* path = new Path("resources/directorytest", "directorytest/");
    FileHeader* result = createFileHeader(path, 0);
    
    CPPUNIT_ASSERT(result->compare(*expected));
    
    delete path;
    delete expected;
}

void FileHeaderTest::testCreateFileHeaderGivenANull()
{
    CPPUNIT_ASSERT(createFileHeader(NULL, 0) == NULL);
}

void FileHeaderTest::testGetBufferGivenAFile()
{
    Path* path = new Path("resources/song.mp3", "song.mp3");
    FileHeader* fileHeader = createFileHeader(path, 0);
    char* buffer = 0;
    int size = fileHeader->size();
    char* expected = (char*) malloc(size);
    memcpy(expected, &fileHeader->headerSignature, sizeof(int));
    memcpy(expected + 4, &fileHeader->versionToExtract, sizeof(short));
    memcpy(expected + 6, &fileHeader->flag, sizeof(short));
    memcpy(expected + 8, &fileHeader->compressionMethod, sizeof(short));
    memcpy(expected + 10, &fileHeader->lastModificationTime, sizeof(short));
    memcpy(expected + 12, &fileHeader->lastModificationDate, sizeof(short));
    memcpy(expected + 14, &fileHeader->crc, sizeof(int));
    memcpy(expected + 18, &fileHeader->compressedSize, sizeof(int));
    memcpy(expected + 22, &fileHeader->unCompressedSize, sizeof(int));
    memcpy(expected + 26, &fileHeader->fileNameLength, sizeof(short));
    memcpy(expected + 28, &fileHeader->extraFieldLength, sizeof(short));
    memcpy(expected + 30, fileHeader->fileName.c_str(), fileHeader->fileNameLength);
    memcpy(expected + 30 + fileHeader->fileNameLength, fileHeader->extraField,
            fileHeader->extraFieldLength);
    memcpy(expected + 30 + fileHeader->fileNameLength + fileHeader->extraFieldLength,
            fileHeader->data, fileHeader->dataSize);
    getBuffer(fileHeader, buffer);
    
    CPPUNIT_ASSERT(memcmp(buffer, expected, size) == 0);
    
    delete path;
    free(buffer);
    free(expected);
}

void FileHeaderTest::testGetBufferGivenADirectory()
{
    Path* path = new Path("resources/directorytest", "directorytest");
    FileHeader* fileHeader = createFileHeader(path, 0);
    char* buffer = 0;
    char* expected = (char*) malloc(fileHeader->size());
    memcpy(expected, &fileHeader->headerSignature, sizeof(int));
    memcpy(expected + 4, &fileHeader->versionToExtract, sizeof(short));
    memcpy(expected + 6, &fileHeader->flag, sizeof(short));
    memcpy(expected + 8, &fileHeader->compressionMethod, sizeof(short));
    memcpy(expected + 10, &fileHeader->lastModificationTime, sizeof(short));
    memcpy(expected + 12, &fileHeader->lastModificationDate, sizeof(short));
    memcpy(expected + 14, &fileHeader->crc, sizeof(int));
    memcpy(expected + 18, &fileHeader->compressedSize, sizeof(int));
    memcpy(expected + 22, &fileHeader->unCompressedSize, sizeof(int));
    memcpy(expected + 26, &fileHeader->fileNameLength, sizeof(short));
    memcpy(expected + 28, &fileHeader->extraFieldLength, sizeof(short));
    memcpy(expected + 30, fileHeader->fileName.c_str(), fileHeader->fileNameLength);
    memcpy(expected + 30 + fileHeader->fileNameLength, fileHeader->extraField,
            fileHeader->extraFieldLength);
    memcpy(expected + 30 + fileHeader->fileNameLength + fileHeader->extraFieldLength,
            fileHeader->data, fileHeader->dataSize);
    getBuffer(fileHeader, buffer);
    
    CPPUNIT_ASSERT(memcmp(buffer, expected, fileHeader->size()) == 0);
    
    delete path;
    free(expected);
    free(buffer);
}

void FileHeaderTest::testGetBufferGivenANull()
{
    char* expected = NULL;
    char* buffer = 0;
    getBuffer(NULL, buffer);
    CPPUNIT_ASSERT(buffer == expected);
}
