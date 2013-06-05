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
    char** input=new char*[1];
    input[0]=(char*)"nonExistantFile";
    ErrorCode code = compress((char*)"nonExistantDir",input, 1, 0);   
    CPPUNIT_ASSERT_EQUAL(FILE_NOT_FOUND, code);
}
