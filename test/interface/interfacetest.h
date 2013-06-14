/*
 * File:   InterfaceTest.h
 * Author: Daniela Meneses
 * Description: Implement test for the communication with the zipper library.
 *
 * Created on May 14, 2013, 4:34:02 PM
 */

#ifndef INTERFACETEST_H
#define	INTERFACETEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "zipperlib.h"

class InterfaceTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(InterfaceTest);

    CPPUNIT_TEST(testCompressionTask);
    CPPUNIT_TEST(testTraverseTaskWithANonZipFile);
    CPPUNIT_TEST(testTraverseTaskWithANonExistentFile);
    CPPUNIT_TEST(testTraverseTaskWithAZipFile);
    CPPUNIT_TEST(testTraverseTaskWithANullPath);
    
    CPPUNIT_TEST(testDecompressTaskGivenAZipWithOneFile);
    CPPUNIT_TEST(testDecompressTaskGivenAZipWithSeveralFiles);
    CPPUNIT_TEST(testDecompressTaskGivenANonZipFile);
    CPPUNIT_TEST(testDecompressTaskGivenANULL);

    CPPUNIT_TEST_SUITE_END();

public:
    InterfaceTest();
    virtual ~InterfaceTest();
    void setUp();
    void tearDown();

private:
    void testCompressionTask();
    void testTraverseTaskWithANonZipFile();
    void testTraverseTaskWithANonExistentFile();
    void testTraverseTaskWithAZipFile();
    void testTraverseTaskWithANullPath();
    
    void testDecompressTaskGivenAZipWithOneFile();
    void testDecompressTaskGivenAZipWithSeveralFiles();
    void testDecompressTaskGivenANonZipFile();
    void testDecompressTaskGivenANULL();
};

#endif	/* INTERFACETEST_H */

