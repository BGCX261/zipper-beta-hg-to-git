/*
 * File:   InterfaceTest.h
 * Author: dann
 *
 * Created on May 14, 2013, 4:34:02 PM
 */

#ifndef INTERFACETEST_H
#define	INTERFACETEST_H

#include <cppunit/extensions/HelperMacros.h>

class InterfaceTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(InterfaceTest);

    CPPUNIT_TEST(testCompressionTask);

    CPPUNIT_TEST_SUITE_END();

public:
    InterfaceTest();
    virtual ~InterfaceTest();
    void setUp();
    void tearDown();

private:
    void testCompressionTask();
};

#endif	/* INTERFACETEST_H */

