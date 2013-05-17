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

