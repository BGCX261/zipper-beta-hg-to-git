/*
 * File:   dateconvertertest.h
 * Author: Luis Aguirre
 * Description: Test the DateConverter class
 *
 * Created on 07-06-2013, 07:02:50 PM
 */

#ifndef DATECONVERTERTEST_H
#define	DATECONVERTERTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "utils/dateconverter.h"

class DateConverterTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(DateConverterTest);

    CPPUNIT_TEST(testParseDate);
    CPPUNIT_TEST(testParseDate2);
    CPPUNIT_TEST(testParseDateGivenValuesInZero);
    CPPUNIT_TEST(testParseDateGivenANull);
    
    CPPUNIT_TEST(testParseTime);
    CPPUNIT_TEST(testParseTime2);
    CPPUNIT_TEST(testParseTimeGivenValuesInZero);
    CPPUNIT_TEST(testParseTimeGivenANull);
    
    CPPUNIT_TEST(testParseMSDosToTm);

    CPPUNIT_TEST_SUITE_END();

public:
    DateConverterTest();
    virtual ~DateConverterTest();
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
    
    void testParseMSDosToTm();
};

#endif	/* DATECONVERTERTEST_H */

