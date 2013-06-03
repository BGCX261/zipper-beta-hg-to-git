/*
 * File:   zipperutils.cpp
 * Author: luis
 *
 * Created on 21-05-2013, 04:43:41 PM
 */

#include "zipperutilstest.h"
#include "utils/zipperutils.h"
#include <list>
#include <stdlib.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ZipperUtilsTest);

ZipperUtilsTest::ZipperUtilsTest()
{
}

ZipperUtilsTest::~ZipperUtilsTest()
{
}

void ZipperUtilsTest::setUp()
{
}

void ZipperUtilsTest::tearDown()
{
}

void ZipperUtilsTest::testParseDate()
{
    struct tm date;
    date.tm_year = 2011 - 1900; //Following the tm structure
    date.tm_mon = 6 - 1; //Following the tm structure
    date.tm_mday = 29;
    short expected = 16093;
    short result = parseDateToMSDosFormat(&date);
    
    CPPUNIT_ASSERT(result == expected);
}

void ZipperUtilsTest::testParseDate2()
{
    struct tm date;
    date.tm_year = 2013 - 1900; //Following the tm structure
    date.tm_mon = 2 - 1; //Following the tm structure
    date.tm_mday = 4;
    short expected = 16964;
    short result = parseDateToMSDosFormat(&date);
    
    CPPUNIT_ASSERT(result == expected);
}

void ZipperUtilsTest::testParseDateGivenValuesInZero()
{
    struct tm date;
    date.tm_year = 0 - 1900; //Following the tm structure
    date.tm_mon = 0 - 1; //Following the tm structure
    date.tm_mday = 0;
    short expected = 0;
    short result = parseDateToMSDosFormat(&date);
    
    CPPUNIT_ASSERT(result == expected);
}

void ZipperUtilsTest::testParseDateGivenANull()
{
    CPPUNIT_ASSERT(parseDateToMSDosFormat(NULL) == 0);
}

void ZipperUtilsTest::testParseTime()
{
    struct tm time;
    time.tm_hour = 11;
    time.tm_min = 30;
    time.tm_sec = 8;
    short expected = 23492;
    short result = parseTimeToMSDosFormat(&time);
    
    CPPUNIT_ASSERT(result == expected);
}

void ZipperUtilsTest::testParseTime2()
{
    struct tm time;
    time.tm_hour = 22;
    time.tm_min = 12;
    time.tm_sec = 20;
    short expected = 45450;
    short result = parseTimeToMSDosFormat(&time);
    
    CPPUNIT_ASSERT(result == expected);
}

void ZipperUtilsTest::testParseTimeGivenValuesInZero()
{
    struct tm time;
    time.tm_hour = 0;
    time.tm_min = 0;
    time.tm_sec = 0;
    short expected = 0;
    short result = parseTimeToMSDosFormat(&time);
    
    CPPUNIT_ASSERT(result == expected);
}

void ZipperUtilsTest::testParseTimeGivenANull()
{
    CPPUNIT_ASSERT(parseTimeToMSDosFormat(NULL) == 0);
}

void ZipperUtilsTest::testNavigateGivenAZipWithOneFile()
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

void ZipperUtilsTest::testNavigateGivenAZipWithSeveralFiles()
{
    std::list<FileHeader*> fileHeaders = navigate("resources/severalFiles.zip");
    CPPUNIT_ASSERT(fileHeaders.size() == 7);
}

void ZipperUtilsTest::testNavigateGivenANonZipFile()
{
    CPPUNIT_ASSERT_THROW(navigate("resources/song.mp3"), NotZipFileException);
}

void ZipperUtilsTest::testNavigateGivenANonExistentFile()
{
    CPPUNIT_ASSERT_THROW(navigate("resources/someFile.zip"), FileNotFoundExpcetion);
}