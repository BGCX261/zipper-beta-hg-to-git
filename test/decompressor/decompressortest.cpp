/*
 * File:   decompressortest.cpp
 * Author: Luis Aguirre
 *
 * Created on 05-06-2013, 04:27:23 PM
 */

#include <stdlib.h>
#include "decompressortest.h"
#include "utils/fileutils.h"

CPPUNIT_TEST_SUITE_REGISTRATION(DecompressorTest);

DecompressorTest::DecompressorTest()
{
}

DecompressorTest::~DecompressorTest()
{
}

void DecompressorTest::setUp()
{
}

void DecompressorTest::tearDown()
{
}

void DecompressorTest::testNavigateGivenAZipWithOneFile()
{
    std::list<FileHeader*> fileHeaders = navigate("resources/oneFile.zip");
    
    FileHeader* expected = new FileHeader();
    
    FILE* file = fopen("resources/directorytestresume", "rb");
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* data = (char*) malloc(size);
    fread(data, sizeof(char), size, file);
    fclose(file);
    
    expected->versionToExtract = 10;
    expected->lastModificationTime = 35450;
    expected->lastModificationDate = 17091;
    expected->crc = 0xE58D0B9E;
    expected->compressedSize = 375;
    expected->uncompressedSize = 375;
    expected->fileNameLength = 19;
    expected->fileName = "directorytestresume";
    expected->setData(data, size);
    
    FileHeader* result = fileHeaders.back();
    
    CPPUNIT_ASSERT(fileHeaders.size() == 1);
    CPPUNIT_ASSERT(result->compare(*result));
    
    free(data);
    delete expected;
}

void DecompressorTest::testNavigateGivenAZipWithSeveralFiles()
{
    std::list<FileHeader*> fileHeaders = navigate("resources/severalFiles.zip");
    CPPUNIT_ASSERT(fileHeaders.size() == 7);
}

void DecompressorTest::testNavigateGivenANonZipFile()
{
    CPPUNIT_ASSERT_THROW(navigate("resources/song.mp3"), NotZipFileException);
}

void DecompressorTest::testNavigateGivenANonExistentFile()
{
    CPPUNIT_ASSERT_THROW(navigate("resources/someFile.zip"), FileNotFoundExpcetion);
}

void DecompressorTest::testDecompressGivenAZipFileWithOneFile()
{
    if(exist("resources/directorytestresume2"))
    {
        remove("resources/directorytestresume2");
    }
    
    CPPUNIT_ASSERT(decompress("resources/oneFile.zip", "resources") == OK);
    CPPUNIT_ASSERT(exist("resources/directorytestresume2"));
}

void DecompressorTest::testDecompressGivenAZipFileWithSeveralFiles()
{
    if(exist("resources/directorytest2"))
    {
        remove("resources/directorytest2/dir1/dir3/file2");
        rmdir("resources/directorytest2/dir1/dir3");
        rmdir("resources/directorytest2/dir1");
        remove("resources/directorytest2/dir2/file3");
        rmdir("resources/directorytest2/dir2");
        remove("resources/directorytest2/file1");
        rmdir("resources/directorytest2");
    }
    
    CPPUNIT_ASSERT(decompress("resources/severalFiles.zip", "resources") == OK);
    
    CPPUNIT_ASSERT(exist("resources/directorytest2"));
    CPPUNIT_ASSERT(exist("resources/directorytest2/dir1"));
    CPPUNIT_ASSERT(exist("resources/directorytest2/dir1/dir3"));
    CPPUNIT_ASSERT(exist("resources/directorytest2/dir1/dir3/file2"));
    CPPUNIT_ASSERT(exist("resources/directorytest2/dir2"));
    CPPUNIT_ASSERT(exist("resources/directorytest2/dir2/file3"));
    CPPUNIT_ASSERT(exist("resources/directorytest2/file1"));
}

void DecompressorTest::testDecompressGivenANonZipFile()
{
    CPPUNIT_ASSERT(decompress("resources/binaryDoc.pdf", "resources") == INVALID_PARAMETERS);
}

void DecompressorTest::testDecompressGivenANonExistentFile()
{
    CPPUNIT_ASSERT(decompress("resources/some.zip", "resources") == FILE_NOT_FOUND);
}

void DecompressorTest::testDecompressGivenANull()
{
    CPPUNIT_ASSERT(decompress(NULL, "resources") == INVALID_PARAMETERS);
}