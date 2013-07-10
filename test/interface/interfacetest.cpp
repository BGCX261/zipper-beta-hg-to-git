/*
 * File:   InterfaceTest.cpp
 * Author: Daniela Meneses
 * Description: Test implementation.
 *
 * Created on May 14, 2013, 4:34:02 PM
 */

#include "interfacetest.h"
#include "utils/fileutils.h"

CPPUNIT_TEST_SUITE_REGISTRATION(InterfaceTest);

InterfaceTest::InterfaceTest()
{
}

InterfaceTest::~InterfaceTest()
{
}

void InterfaceTest::setUp()
{
}

void InterfaceTest::tearDown()
{
    if (exist("resources/testFile"))
        remove("resources/testFile");
    
    if (exist("resources/song.zip"))
        remove("resources/song.zip");
    
    if (exist("resources/directorytest/song.mp3"))
        remove("resources/directorytest/song.mp3");
    
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
}

void InterfaceTest::testCompressionTask()
{
    char** input = new char*[1];
    input[0] = (char*) "nonExistentFile"; 
    ErrorCode code = compress((char*) "nonExistentDir", input, 1, 0);
    CPPUNIT_ASSERT_EQUAL(FILE_NOT_FOUND, code);
    delete[] input;
}

void InterfaceTest::testTraverseTaskWithANonZipFile()
{
    ErrorCode code = traverse("resources/song.mp3", -1);
    CPPUNIT_ASSERT_EQUAL(INVALID_ZIP_FILE, code);
}

void InterfaceTest::testTraverseTaskWithANonExistentFile()
{
    ErrorCode code = traverse("resources/somefile", -1);
    CPPUNIT_ASSERT_EQUAL(FILE_NOT_FOUND, code);
}

void InterfaceTest::testTraverseTaskWithAZipFile()
{
    ErrorCode code = traverse("resources/oneFile.zip", -1);
    CPPUNIT_ASSERT_EQUAL(OK, code);
}

void InterfaceTest::testTraverseTaskWithANullPath()
{
    ErrorCode code = traverse(NULL, -1);
    CPPUNIT_ASSERT_EQUAL(INVALID_PARAMETERS, code);
}

void InterfaceTest::testDecompressTaskGivenAZipWithOneFile()
{
    decompress("resources/oneFile.zip", "resources");
    CPPUNIT_ASSERT(decompress("resources/oneFile.zip", "resources") == OK);
    CPPUNIT_ASSERT(exist("resources/testFile"));
    
    //Test the content
    FILE* file = fopen("resources/testFile", "rb");
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* data = (char*) malloc(size);
    fread(data, sizeof(char), size, file);
    CPPUNIT_ASSERT(memcmp(data, "Sample", size) == 0);
    fclose(file);
    free(data);
}

void InterfaceTest::testDecompressTaskGivenAZipWithSeveralFiles()
{
    CPPUNIT_ASSERT(decompress("resources/severalFiles.zip", "resources") == OK);
    
    CPPUNIT_ASSERT(exist("resources/directorytest2"));
    CPPUNIT_ASSERT(exist("resources/directorytest2/dir1"));
    CPPUNIT_ASSERT(exist("resources/directorytest2/dir1/dir3"));
    CPPUNIT_ASSERT(exist("resources/directorytest2/dir1/dir3/file2"));
    CPPUNIT_ASSERT(exist("resources/directorytest2/dir2"));
    CPPUNIT_ASSERT(exist("resources/directorytest2/dir2/file3"));
    CPPUNIT_ASSERT(exist("resources/directorytest2/file1"));
    
    //Test the content
    FILE* file = fopen("resources/directorytest2/dir1/dir3/file2", "rb");
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* data = (char*) malloc(size);
    fread(data, sizeof(char), size, file);
    fclose(file);
    CPPUNIT_ASSERT(memcmp(data, "hello2\n", size) == 0);
    free(data);
    
    file = fopen("resources/directorytest2/dir2/file3", "rb");
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);
    data = (char*) malloc(size);
    fread(data, sizeof(char), size, file);
    fclose(file);
    CPPUNIT_ASSERT(memcmp(data, "hello3\n", size) == 0);
    free(data);
    
    file = fopen("resources/directorytest2/file1", "rb");
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);
    data = (char*) malloc(size);
    fread(data, sizeof(char), size, file);
    fclose(file);
    CPPUNIT_ASSERT(memcmp(data, "hello1\n", size) == 0);
    free(data);
}

void InterfaceTest::testDecompressTaskGivenANonZipFile()
{
    CPPUNIT_ASSERT(decompress("resources/binaryDoc.pdf", "resources") == INVALID_ZIP_FILE);
}

void InterfaceTest::testDecompressTaskGivenANULL()
{
    CPPUNIT_ASSERT(decompress(NULL, "resources") == INVALID_PARAMETERS);
}

void InterfaceTest::testCompressAndDecompressAFileWithBz2Lib()
{
    char** input = new char*[1];
    input[0] = (char*) "resources/song.mp3"; 
    CPPUNIT_ASSERT(compress((char*) "resources/", input, 1, 12) == OK);
    CPPUNIT_ASSERT(exist("resources/song.zip"));
    CPPUNIT_ASSERT(decompress("resources/song.zip", "resources/directorytest") == OK);
    CPPUNIT_ASSERT(exist("resources/directorytest/song.mp3"));
    
    FILE* expected = fopen("resources/song.mp3", "rb");
    fseek(expected, 0, SEEK_END);
    int expectedSize = ftell(expected);
    fseek(expected, 0, SEEK_SET);
    char* expectedData = (char*) malloc(expectedSize);
    fread(expectedData, sizeof(char), expectedSize, expected);
    fclose(expected);
    
    FILE* result = fopen("resources/directorytest/song.mp3", "rb");
    fseek(result, 0, SEEK_END);
    int resultSize = ftell(result);
    fseek(result, 0, SEEK_SET);
    char* resultData = (char*) malloc(resultSize);
    fread(resultData, sizeof(char), resultSize, result);
    fclose(result);
    
    CPPUNIT_ASSERT(expectedSize == resultSize);
    CPPUNIT_ASSERT(memcmp(expectedData, resultData, expectedSize) == 0);
    delete[] input;
    free(expectedData);
    free(resultData);
}