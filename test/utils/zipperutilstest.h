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
    CPPUNIT_TEST(testParseDate2);
    CPPUNIT_TEST(testParseDateGivenValuesInZero);
    CPPUNIT_TEST(testParseDateGivenANull);
    
    CPPUNIT_TEST(testParseTime);
    CPPUNIT_TEST(testParseTime2);
    CPPUNIT_TEST(testParseTimeGivenValuesInZero);
    CPPUNIT_TEST(testParseTimeGivenANull);
    
    CPPUNIT_TEST(testNavigateGivenAZipWithOneFile);
    CPPUNIT_TEST(testNavigateGivenAZipWithSeveralFiles);
    CPPUNIT_TEST(testNavigateGivenANonZipFile);
    CPPUNIT_TEST(testNavigateGivenANonExistentFile);

    CPPUNIT_TEST_SUITE_END();

public:
    ZipperUtilsTest();
    virtual ~ZipperUtilsTest();
    void setUp();
    void tearDown();

private:
    void testParseDate();
    void testParseDate2();
    void testParseDateGivenValuesInZero();
    void testParseDateGivenANull();
    
    void testParseTime();
    void testParseTime2();
    void testParseTimeGivenValuesInZero();
    void testParseTimeGivenANull();
    
    void testNavigateGivenAZipWithOneFile();
    void testNavigateGivenAZipWithSeveralFiles();
    void testNavigateGivenANonZipFile();
    void testNavigateGivenANonExistentFile();
};

#endif	/* ZIPPERUTILS_H */

