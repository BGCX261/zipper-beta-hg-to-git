/*
 * File:   InterfaceTest.cpp
 * Author: Daniela Meneses
 * Description: Test implementation.
 *
 * Created on May 14, 2013, 4:34:02 PM
 */

#include "interfacetest.h"

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
}

void InterfaceTest::testCompressionTask()
{
    char** input = new char*[1];
    input[0] = (char*) "nonExistentFile"; 
    ErrorCode code = compress((char*) "nonExistentDir", input, 1, 0);
    CPPUNIT_ASSERT_EQUAL(FILE_NOT_FOUND, code);
}

void InterfaceTest::testTraverseTaskWithANonZipFile()
{
    ErrorCode code = traverse("resources/song.mp3");
    CPPUNIT_ASSERT_EQUAL(INVALID_ZIP_FILE, code);
}

void InterfaceTest::testTraverseTaskWithANonExistentFile()
{
    ErrorCode code = traverse("resources/somefile");
    CPPUNIT_ASSERT_EQUAL(FILE_NOT_FOUND, code);
}

void InterfaceTest::testTraverseTaskWithAZipFile()
{
    ErrorCode code = traverse("resources/oneFile.zip");
    CPPUNIT_ASSERT_EQUAL(OK, code);
}

void InterfaceTest::testTraverseTaskWithANullPath()
{
    ErrorCode code = traverse(NULL);
    CPPUNIT_ASSERT_EQUAL(INVALID_PARAMETERS, code);
}