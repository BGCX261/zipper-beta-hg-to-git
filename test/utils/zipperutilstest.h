/*
 * File:   zipperutilstest.h
 * Author: Luis Aguirre
 * Description: Implement tests for the utils functions that use the compressor.
 *
 * Created on 21-05-2013, 04:43:40 PM
 */

#ifndef ZIPPERUTILSTEST_H
#define	ZIPPERUTILSTEST_H

#include <cppunit/extensions/HelperMacros.h>

class ZipperUtilsTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(ZipperUtilsTest);

    CPPUNIT_TEST(testParseDate);
    CPPUNIT_TEST(testParseDateGivenValuesInZero);
    CPPUNIT_TEST(testParseDateGivenANull);
    
    CPPUNIT_TEST(testParseTime);
    CPPUNIT_TEST(testParseTimeGivenValuesInZero);
    CPPUNIT_TEST(testParseTimeGivenANull);

    CPPUNIT_TEST_SUITE_END();

public:
    ZipperUtilsTest();
    virtual ~ZipperUtilsTest();
    void setUp();
    void tearDown();

private:
    void testParseDate();
    void testParseDateGivenValuesInZero();
    void testParseDateGivenANull();
    
    void testParseTime();
    void testParseTimeGivenValuesInZero();
    void testParseTimeGivenANull();
};

#endif	/* ZIPPERUTILS_H */

