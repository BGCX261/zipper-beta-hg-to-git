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
    ErrorCode code = compress(NULL, NULL, 0, 0);   
    CPPUNIT_ASSERT_EQUAL(FILE_NOT_FOUND, code);
}
