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
    if(exist("resources/File1.txt"))
    {
        remove("resources/File1.txt");
    }
    if(exist("resources/FolderTest"))
    {
        rmdir("resources/FolderTest");
    }
}

void DecompressorTest::testNavigateGivenAZipWithOneFile()
{
    std::list<FileHeader*> fileHeaders = navigate("resources/oneFile.zip");
    
    FileHeader* expected = new FileHeader();
    
    expected->versionToExtract = 778;
    expected->lastModificationTime = 37190;
    expected->lastModificationDate = 15515;
    expected->crc = 0xF6A773F5;
    expected->compressedSize = 6;
    expected->uncompressedSize = 6;
    expected->fileNameLength = 8;
    expected->fileName = "testFile";
    expected->setData("Sample", 6);
    
    FileHeader* result = fileHeaders.back();
    
    CPPUNIT_ASSERT(fileHeaders.size() == 1);
    CPPUNIT_ASSERT(result->compare(*expected));
    
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

void DecompressorTest::testDecompressAFileHeaderGivenAFile()
{
    FileHeader* fileHeader = new FileHeader();
    fileHeader->fileName = "File1.txt";
    fileHeader->fileNameLength = 9;
    fileHeader->versionToExtract = 10;
    fileHeader->compressionMethod = 0;
    fileHeader->flag = 0;
    fileHeader->crc = 0x70FCDC28;
    fileHeader->lastModificationTime = 34568;
    fileHeader->lastModificationDate = 24963;
    fileHeader->compressedSize = 17;
    fileHeader->uncompressedSize = 17;
    fileHeader->setData("this is a sample", 0);
    fileHeader->setExtraField("", 0);
    
    decompressAFileHeader(fileHeader, "resources");
    CPPUNIT_ASSERT(exist("resources/File1.txt"));
    CPPUNIT_ASSERT(isFile("resources/File1.txt"));
}

void DecompressorTest::testDecompressAFileHeaderGivenADirectory()
{
    FileHeader* fileHeader = new FileHeader();
    fileHeader->fileName = "FolderTest/";
    fileHeader->fileNameLength = 11;
    fileHeader->versionToExtract = 10;
    fileHeader->compressionMethod = 0;
    fileHeader->flag = 0;
    fileHeader->crc = 0;
    fileHeader->lastModificationTime = 0;
    fileHeader->lastModificationDate = 0;
    fileHeader->compressedSize = 0;
    fileHeader->uncompressedSize = 0;
    
    decompressAFileHeader(fileHeader, "resources");
    CPPUNIT_ASSERT(exist("resources/FolderTest"));
    CPPUNIT_ASSERT(isDirectory("resources/FolderTest"));
}

void DecompressorTest::testDecompressAFileHeaderGivenANull()
{
    CPPUNIT_ASSERT_THROW(decompressAFileHeader(NULL, "resources"), DecompressException);
}
