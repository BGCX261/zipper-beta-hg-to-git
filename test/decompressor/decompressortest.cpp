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
    if (exist("resources/File1.txt"))
    {
        remove("resources/File1.txt");
    }
    if (exist("resources/FolderTest"))
    {
        rmdir("resources/FolderTest");
    }
}

void DecompressorTest::testNavigateGivenAZipWithOneFile()
{
    std::list<FileHeader*> fileHeaders;
    navigate("resources/oneFile.zip", fileHeaders);

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
    freeList(fileHeaders);
}

void DecompressorTest::testNavigateGivenAZipWithSeveralFiles()
{
    std::list<FileHeader*> fileHeaders;
    navigate("resources/severalFiles.zip", fileHeaders);
    CPPUNIT_ASSERT(fileHeaders.size() == 7);
    freeList(fileHeaders);
}

void DecompressorTest::testNavigateGivenANonZipFile()
{
    std::list<FileHeader*> fileHeaders;
    CPPUNIT_ASSERT_THROW(navigate("resources/song.mp3", fileHeaders), NotZipFileException);
    freeList(fileHeaders);
}

void DecompressorTest::testNavigateGivenANonExistentFile()
{
    std::list<FileHeader*> fileHeaders;
    CPPUNIT_ASSERT_THROW(navigate("resources/someFile.zip", fileHeaders), FileNotFoundExpcetion);
    freeList(fileHeaders);
}

void freeList(std::list<FileHeader*>& fileHeaders)
{
    for (std::list<FileHeader*>::iterator it = fileHeaders.begin(); it != fileHeaders.end(); it++)
    {
        delete *it;
    }
    fileHeaders.clear();
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
    fileHeader->lastModificationTime = 22568;
    fileHeader->lastModificationDate = 16076;
    fileHeader->compressedSize = 17;
    fileHeader->uncompressedSize = 17;
    fileHeader->setData("this is a sample", 0);
    fileHeader->setExtraField("", 0);

    decompressAFileHeader(fileHeader, "resources");
    CPPUNIT_ASSERT(exist("resources/File1.txt"));
    CPPUNIT_ASSERT(isFile("resources/File1.txt"));
    tm* date = recoverLastModificationDateAndTime("resources/File1.txt");
    CPPUNIT_ASSERT(date->tm_year == 2011 - 1900);
    CPPUNIT_ASSERT(date->tm_mon == 6 - 1);
    CPPUNIT_ASSERT(date->tm_mday == 12);
    CPPUNIT_ASSERT(date->tm_hour == 11);
    CPPUNIT_ASSERT(date->tm_min == 1);
    CPPUNIT_ASSERT(date->tm_sec == 8 * 2);
    delete fileHeader;
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
    delete fileHeader;
}

void DecompressorTest::testDecompressAFileHeaderGivenANull()
{
    CPPUNIT_ASSERT_THROW(decompressAFileHeader(NULL, "resources"), DecompressException);
}

void DecompressorTest::testLastModificationTimeOfADecompressedFile()
{
    FileHeader* fileHeader = new FileHeader();
    fileHeader->fileName = "File1.txt";
    fileHeader->fileNameLength = 9;
    fileHeader->versionToExtract = 10;
    fileHeader->compressionMethod = 0;
    fileHeader->flag = 0;
    fileHeader->crc = 0x70FCDC28;
    fileHeader->lastModificationTime = 23492;
    fileHeader->lastModificationDate = 16093;
    fileHeader->compressedSize = 17;
    fileHeader->uncompressedSize = 17;
    fileHeader->setData("this is a sample", 0);
    fileHeader->setExtraField("", 0);
    decompressAFileHeader(fileHeader, "resources");

    tm* result = recoverLastModificationDateAndTime("resources/File1.txt");

    CPPUNIT_ASSERT(result->tm_year == 2011 - 1900);
    CPPUNIT_ASSERT(result->tm_mon == 6 - 1);
    CPPUNIT_ASSERT(result->tm_mday == 29);
    CPPUNIT_ASSERT(result->tm_hour == 11);
    CPPUNIT_ASSERT(result->tm_min == 30);
    CPPUNIT_ASSERT(result->tm_sec == 8);
    delete fileHeader;
}
