/*
 * File:   FileUtilsTest.cpp
 * Author: Daniela Meneses
 * Description: Test implementation
 *
 * Created on May 16, 2013, 3:28:30 PM
 */

#include "fileutilstest.h"
#include <stdlib.h>
#include <fstream>
#include <stdlib.h>
#include <fstream>


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

void FileUtilsTest::testListFilesFromADirectory()
{
    int expectedFilesCount = 7;
    int inputCount = 1;
    const char* directory = "resources/directorytest";
    const char** paths = (const char**) calloc(inputCount, sizeof (char*));
    paths[0] = directory;
    std::list<Path>* files = getFiles(paths, inputCount);
    int filesCount = files->size();
    CPPUNIT_ASSERT_EQUAL(expectedFilesCount, filesCount);

    free(paths);
}

void FileUtilsTest::testListFilesFromManyDirectories()
{
    int expectedFilesCount = 6;
    int inputCount = 3;
    const char* directory1 = "resources/directorytest/dir1";
    const char* directory2 = "resources/directorytest/dir2";
    const char* file1 = "resources/directorytest/file1";
    const char** paths = (const char**) calloc(inputCount, sizeof (char*));
    paths[0] = directory1;
    paths[1] = directory2;
    paths[2] = file1;
    std::list<Path>* files = getFiles(paths, inputCount);
    int filesCount = files->size();
    CPPUNIT_ASSERT_EQUAL(expectedFilesCount, filesCount);

    free(paths);
}

void FileUtilsTest::testListFilesWhenAFileDoesNotExist()
{
    int inputCount = 1;
    const char* falseDirectory = "resources/somedirectory";
    const char** paths = (const char**) calloc(inputCount, sizeof (char*));
    paths[0] = falseDirectory;

    CPPUNIT_ASSERT_THROW(getFiles(paths, inputCount), FileNotFoundExpcetion);

    free(paths);
}

void FileUtilsTest::testListFilesWhenAPathIsNull()
{
    int inputCount = 1;
    const char* falseDirectory = NULL;
    const char** paths = (const char**) calloc(inputCount, sizeof (char*));
    paths[0] = falseDirectory;

    CPPUNIT_ASSERT_THROW(getFiles(paths, inputCount), NullPathException);
}

void FileUtilsTest::testListFilesCheckNames()
{
    int inputCount = 1;
    const char* directory = "resources/directorytest";
    const char** paths = (const char**) calloc(inputCount, sizeof (char*));
    paths[0] = directory;
    std::list<Path>* files = getFiles(paths, inputCount);
    int filesCount = files->size();

    std::string newLine;
    std::ifstream file;
    file.open("resources/directorytestresume");
    int testCount = 0;

    while (testCount < filesCount)
    {
        getline(file, newLine);
        Path path = files->front();
        files->pop_front();
        CPPUNIT_ASSERT(newLine.compare(path.fullPath) == 0);
        files->push_back(path);
        testCount++;
    }

    testCount = 0;

    while (testCount < filesCount)
    {
        getline(file, newLine);
        Path path = files->front();
        files->pop_front();
        CPPUNIT_ASSERT(newLine.compare(path.relativePath) == 0);
        files->push_back(path);
        testCount++;
    }

    file.close();
}

void FileUtilsTest::testGetFileName()
{
    std::string expected = "file1";
    std::string response = getFileName("/folder/file1");
    CPPUNIT_ASSERT(expected.compare(response) == 0);
}

void FileUtilsTest::testGetFileNameWhenItDoesnNotHaveASlash()
{
    std::string expected = "somefile";
    std::string response = getFileName("somefile");
    CPPUNIT_ASSERT(expected.compare(response) == 0);
}

void FileUtilsTest::testGetFileNameWhenIsNullPath()
{    
    std::string expected;
    std::string response = getFileName(expected);
    CPPUNIT_ASSERT(expected.compare(response) == 0);
}

void FileUtilsTest::testRecoverLastModiticationTDGivenAFile()
{
    int year = 2013 - 1900; /*Following the tm structure format*/
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