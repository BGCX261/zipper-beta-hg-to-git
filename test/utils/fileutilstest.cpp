/*
 * File:   FileUtilsTest.cpp
 * Author: Daniela Meneses
 * Description: Test implementation
 *
 * Created on May 16, 2013, 3:28:30 PM
 */

#include "fileutilstest.h"
#include "../compressor/fileheadertest.h"
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <time.h>
#include <utime.h>
#include <stdio.h>


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
    const char* path = "resources/folder";
    if (exist(path))
    {
        rmdir(path);
    }
    if (exist("resources/testFile"))
    {
        remove("resources/testFile");
    }
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
    std::list<Path> files;
    explorePaths(paths, inputCount, files);
    int filesCount = files.size();
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
    std::list<Path> files;
    explorePaths(paths, inputCount, files);
    int filesCount = files.size();
    CPPUNIT_ASSERT_EQUAL(expectedFilesCount, filesCount);

    free(paths);
}

void FileUtilsTest::testListFilesWhenAFileDoesNotExist()
{
    int inputCount = 1;
    const char* falseDirectory = "resources/somedirectory";
    const char** paths = (const char**) calloc(inputCount, sizeof (char*));
    paths[0] = falseDirectory;
    std::list<Path> files;
    CPPUNIT_ASSERT_THROW(explorePaths(paths, inputCount, files), FileNotFoundExpcetion);

    free(paths);
}

void FileUtilsTest::testListFilesWhenAPathIsNull()
{
    int inputCount = 1;
    const char* falseDirectory = NULL;
    const char** paths = (const char**) calloc(inputCount, sizeof (char*));
    paths[0] = falseDirectory;
    std::list<Path> files;
    CPPUNIT_ASSERT_THROW(explorePaths(paths, inputCount, files), NullPathException);
    free(paths);
}

bool fileComparator(const Path& first, const Path& second)
{
    return strcasecmp(first.fullPath.c_str(), second.fullPath.c_str()) <= 0;
}

void FileUtilsTest::testListFilesCheckNames()
{
    int inputCount = 1;
    const char* directory = "resources/directorytest";
    const char** paths = (const char**) calloc(inputCount, sizeof (char*));
    paths[0] = directory;
    std::list<Path> files;
    explorePaths(paths, inputCount, files);
    int filesCount = files.size();
    files.sort(fileComparator);

    std::string newLine;
    std::ifstream file;
    file.open("resources/directorytestresume");
    int testCount = 0;

    while (testCount < filesCount)
    {
        getline(file, newLine);
        Path path = files.front();
        files.pop_front();
        std::string message = "Full paths: ";
        message.append(newLine);
        message.append(" != ");
        message.append(path.fullPath);
        CPPUNIT_ASSERT_MESSAGE(message, newLine.compare(path.fullPath) == 0);
        files.push_back(path);
        testCount++;
    }

    testCount = 0;

    while (testCount < filesCount)
    {
        getline(file, newLine);
        Path path = files.front();
        files.pop_front();
        std::string message = "Relative paths: ";
        message.append(newLine);
        message.append(" != ");
        message.append(path.relativePath);
        CPPUNIT_ASSERT_MESSAGE(message, newLine.compare(path.relativePath) == 0);
        files.push_back(path);
        testCount++;
    }

    file.close();
    free(paths);
}

void FileUtilsTest::testGetFileName()
{
    Path path("/folder/file1", false);
    std::string expected = "file1";
    CPPUNIT_ASSERT(expected.compare(path.relativePath) == 0);
}

void FileUtilsTest::testGetFileNameWhenItDoesnNotHaveASlash()
{
    Path path("somefile", false);
    std::string expected = "somefile";
    CPPUNIT_ASSERT(expected.compare(path.relativePath) == 0);
}

void FileUtilsTest::testGetFileNameWhenIsEmpty()
{
    Path path("", false);
    std::string expected = "";
    CPPUNIT_ASSERT(expected.compare(path.relativePath) == 0);
}

void setLastModificationTimeOfAFile(const char* path)
{
    struct utimbuf utimeBuffer;
    struct tm modificationTime;
    memset(&utimeBuffer, 0, sizeof (utimbuf));
    memset(&modificationTime, 0, sizeof (tm));

    modificationTime.tm_year = 2011 - 1900;
    modificationTime.tm_mon = 4;
    modificationTime.tm_mday = 20;
    modificationTime.tm_hour = 17;
    modificationTime.tm_min = 42;
    modificationTime.tm_sec = 22;

    time(&utimeBuffer.actime);
    utimeBuffer.modtime = mktime(&modificationTime);
    utime(path, &utimeBuffer);
}

void FileUtilsTest::testRecoverLastModiticationTDGivenAFile()
{
    setLastModificationTimeOfAFile("resources/song.mp3");

    int year = 2011 - 1900; /*Following the tm structure format*/
    int month = 4;
    int day = 20;
    int hour = 21; /*It does not take account the horary zone*/
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

void FileUtilsTest::testCheckTargetPathWhenTheTargetPathIsValid()
{
    const char* targetPath = "Desktop/other/compressTest.zip";
    const char* otherPath = "Desktop/cpp/main.cpp";

    std::string actualPath = prepareTargetPath(targetPath, otherPath);
    std::string expectedPath = "Desktop/other/compressTest.zip";

    CPPUNIT_ASSERT_EQUAL(actualPath, expectedPath);
}

void FileUtilsTest::testCheckTargetPathWhenTheTargetPathIsInvalidAndTheOtherIsFile()
{
    const char* targetPath = "Desktop/other/compress/";
    const char* otherPath = "Desktop/cpp/main.cpp";

    std::string actualPath = prepareTargetPath(targetPath, otherPath);
    std::string expectedPath = "Desktop/other/compress/main.zip";

    CPPUNIT_ASSERT_EQUAL(actualPath, expectedPath);
}

void FileUtilsTest::testCheckTargetPathWhenTheTargetPathIsInvalidAndTheOtherIsDirectory()
{
    const char* targetPath = "Desktop/other/compress/";
    const char* otherPath = "Desktop/cpp/src";

    std::string actualPath = prepareTargetPath(targetPath, otherPath);
    std::string expectedPath = "Desktop/other/compress/src.zip";

    CPPUNIT_ASSERT_EQUAL(actualPath, expectedPath);
}

void FileUtilsTest::testCheckTargetPathWhenTheTargetDoesNotHaveTheLastSlashAndTheOtherIsFile()
{
    const char* targetPath = "Desktop/other/compress";
    const char* otherPath = "Desktop/cpp/file1.cpp";

    std::string actualPath = prepareTargetPath(targetPath, otherPath);
    std::string expectedPath = "Desktop/other/compress/file1.zip";

    CPPUNIT_ASSERT_EQUAL(actualPath, expectedPath);
}

void FileUtilsTest::testCheckTargetPathWhenTheTargetDoesNotHaveTheLastSlashAndTheOtherIsDirectory()
{
    const char* targetPath = "Desktop/other/compress";
    const char* otherPath = "Desktop/cpp/resources";

    std::string actualPath = prepareTargetPath(targetPath, otherPath);
    std::string expectedPath = "Desktop/other/compress/resources.zip";

    CPPUNIT_ASSERT_EQUAL(actualPath, expectedPath);

}

void FileUtilsTest::testSetLastModificationDateAndTimeGivenAFile()
{
    const char* path = "resources/testFile";
    FILE* file = fopen(path, "wb");
    const char* content = "Sample";
    fwrite(content, sizeof (char), strlen(content), file);
    fclose(file);

    tm* expected = new tm();
    expected->tm_year = 2010 - 1900;
    expected->tm_mon = 4 - 1;
    expected->tm_mday = 27;
    expected->tm_hour = 18;
    expected->tm_min = 10;
    expected->tm_sec = 13;

    CPPUNIT_ASSERT(setLastModificationDateAndTime(path, expected));
    tm* result = recoverLastModificationDateAndTime(path);
    CPPUNIT_ASSERT(expected->tm_year == result->tm_year);
    CPPUNIT_ASSERT(expected->tm_mon == result->tm_mon);
    CPPUNIT_ASSERT(expected->tm_mday == result->tm_mday);
    CPPUNIT_ASSERT(expected->tm_hour == result->tm_hour);
    CPPUNIT_ASSERT(expected->tm_min == result->tm_min);
    CPPUNIT_ASSERT(expected->tm_sec == result->tm_sec);
    delete expected;
}

void FileUtilsTest::testSetLastModificationDateAndTimeGivenADirectory()
{
    tm* expected = new tm();
    const char* path = "resources/directorytest";
    CPPUNIT_ASSERT(!setLastModificationDateAndTime(path, expected));
    delete expected;
}

void FileUtilsTest::testSetLastModificationDateAndTimeGivenANonExistentFile()
{
    tm* expected = new tm();
    CPPUNIT_ASSERT_THROW(!setLastModificationDateAndTime("resources/someFile", expected),
            FileNotFoundExpcetion);
    delete expected;
}

void FileUtilsTest::testSetLastModificationDateAndTimeGivenANull()
{
    CPPUNIT_ASSERT(!setLastModificationDateAndTime("resources/song.mp3", NULL));
}

void FileUtilsTest::testCreateADirectory()
{
    const char* path = "resources/folder";

    CPPUNIT_ASSERT(createADirectory(path));
    CPPUNIT_ASSERT(exist(path));
}

void FileUtilsTest::testCreateADirectoryGivenAExistentDirectory()
{
    const char* path = "resources/folder";
    createADirectory(path);

    CPPUNIT_ASSERT(createADirectory(path));
}

void FileUtilsTest::testCreateADirectoryGivenANull()
{
    CPPUNIT_ASSERT(!createADirectory(NULL));
}
