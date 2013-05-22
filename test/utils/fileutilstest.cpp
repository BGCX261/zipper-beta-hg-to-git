/*
 * File:   FileUtilsTest.cpp
 * Author: Daniela Meneses
 * Description: Test implementation
 *
 * Created on May 16, 2013, 3:28:30 PM
 */

#include "fileutilstest.h"


CPPUNIT_TEST_SUITE_REGISTRATION(FileUtilsTest);

FileUtilsTest::FileUtilsTest()
{
}

FileUtilsTest::~FileUtilsTest()
{
}

void FileUtilsTest::setUp()
{
}

void FileUtilsTest::tearDown()
{
}

void FileUtilsTest::testIsDirectoryWhenExist()
{
    const char* directory = "resources/directorytest";
    bool isDir = isDirectory(directory);
    CPPUNIT_ASSERT_EQUAL(true, isDir);
}

void FileUtilsTest::testIsDirectoryWhenDoNotExist()
{
    const char* directory = "somedirectory";
    bool isDir = isDirectory(directory);
    CPPUNIT_ASSERT_EQUAL(false, isDir);
}

void FileUtilsTest::testIsDirectoryGivenAFile()
{
    const char* directory = "resources/directorytest/file1";
    bool isDir = isDirectory(directory);
    CPPUNIT_ASSERT_EQUAL(false, isDir);
}

void FileUtilsTest::testIsDirectoryGivenANullParam()
{
    bool isDir = isDirectory(NULL);
    CPPUNIT_ASSERT_EQUAL(false, isDir);
}

void FileUtilsTest::testIsFileWhenExist()
{
    const char* file = "resources/directorytest/file1";
    bool isAFile = isFile(file);
    CPPUNIT_ASSERT_EQUAL(true, isAFile);
}

void FileUtilsTest::testIsFileWhenDoNotExist()
{
    const char* file = "somefile";
    bool isAFile = isFile(file);
    CPPUNIT_ASSERT_EQUAL(false, isAFile);
}

void FileUtilsTest::testIsFileGivenADirectory()
{
    const char* file = "resources/directorytest";
    bool isAFile = isFile(file);
    CPPUNIT_ASSERT_EQUAL(false, isAFile);
}

void FileUtilsTest::testIsFileGivenANullParam()
{
    bool isAFile = isFile(NULL);
    CPPUNIT_ASSERT_EQUAL(false, isAFile);
}

void FileUtilsTest::testExistWhenDoExist()
{
    const char* file = "resources/directorytest/file1";
    bool fileExist = exist(file);
    CPPUNIT_ASSERT_EQUAL(true, fileExist);
}

void FileUtilsTest::testExistWhenDoNotExist()
{
    const char* file = "resources/somefile";
    bool fileExist = exist(file);
    CPPUNIT_ASSERT_EQUAL(false, fileExist);
}

void FileUtilsTest::testExistWhenIsNull()
{
    bool fileExist = exist(NULL);
    CPPUNIT_ASSERT_EQUAL(false, fileExist);
}

void FileUtilsTest::testRecoverLastModiticationTDGivenAFile()
{
    /*Following the tm structure format*/
    int year = 2013 - 1900;
    int month = 4;
    int day = 17;
    int hour = 21;  /*It does not take account the horary zone*/
    int minute = 42;
    int second = 22;
    
    tm* result = recoverLastModificationDateAndTime("resources/song.mp3");
    CPPUNIT_ASSERT(result->tm_year == year);
    CPPUNIT_ASSERT(result->tm_mon == month);
    CPPUNIT_ASSERT(result->tm_mday == day);
    CPPUNIT_ASSERT(result->tm_hour == hour);
    CPPUNIT_ASSERT(result->tm_min == minute);
    CPPUNIT_ASSERT(result->tm_sec == second);
    
}

void FileUtilsTest::testRecoverLastModificationTDGivenADirectory()
{
    tm* result = recoverLastModificationDateAndTime("resources/directorytest");
    CPPUNIT_ASSERT(result == NULL);
}

void FileUtilsTest::testRecoverLastModificationTDWhenDoNotExist()
{
    tm* result = recoverLastModificationDateAndTime("resources/notexist");
    CPPUNIT_ASSERT(result == NULL);
}