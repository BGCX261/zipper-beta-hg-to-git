/*
 * File:   zipperutils.cpp
 * Author: luis
 *
 * Created on 21-05-2013, 04:43:41 PM
 */

#include "zipperutilstest.h"
#include "utils/zipperutils.h"


CPPUNIT_TEST_SUITE_REGISTRATION(ZipperUtilsTest);

ZipperUtilsTest::ZipperUtilsTest()
{
}

ZipperUtilsTest::~ZipperUtilsTest()
{
}

void ZipperUtilsTest::setUp()
{
}

void ZipperUtilsTest::tearDown()
{
}

void ZipperUtilsTest::testParseDate()
{
    struct tm date;
    date.tm_year = 2011 - 1900; //Following the tm structure
    date.tm_mon = 6 - 1; //Following the tm structure
    date.tm_mday = 29;
    short expected = 16093;
    short result = parseDateToMSDosFormat(&date);
    
    CPPUNIT_ASSERT(result == expected);
}

void ZipperUtilsTest::testParseDate2()
{
    struct tm date;
    date.tm_year = 2013 - 1900; //Following the tm structure
    date.tm_mon = 2 - 1; //Following the tm structure
    date.tm_mday = 4;
    short expected = 16964;
    short result = parseDateToMSDosFormat(&date);
    
    CPPUNIT_ASSERT(result == expected);
}

void ZipperUtilsTest::testParseDateGivenValuesInZero()
{
    struct tm date;
    date.tm_year = 0 - 1900; //Following the tm structure
    date.tm_mon = 0 - 1; //Following the tm structure
    date.tm_mday = 0;
    short expected = 0;
    short result = parseDateToMSDosFormat(&date);
    
    CPPUNIT_ASSERT(result == expected);
}

void ZipperUtilsTest::testParseDateGivenANull()
{
    CPPUNIT_ASSERT(parseDateToMSDosFormat(NULL) == 0);
}

void ZipperUtilsTest::testParseTime()
{
    struct tm time;
    time.tm_hour = 11;
    time.tm_min = 30;
    time.tm_sec = 8;
    short expected = 23492;
    short result = parseTimeToMSDosFormat(&time);
    
    CPPUNIT_ASSERT(result == expected);
}

void ZipperUtilsTest::testParseTime2()
{
    struct tm time;
    time.tm_hour = 22;
    time.tm_min = 12;
    time.tm_sec = 20;
    short expected = 45450;
    short result = parseTimeToMSDosFormat(&time);
    
    CPPUNIT_ASSERT(result == expected);
}

void ZipperUtilsTest::testParseTimeGivenValuesInZero()
{
    struct tm time;
    time.tm_hour = 0;
    time.tm_min = 0;
    time.tm_sec = 0;
    short expected = 0;
    short result = parseTimeToMSDosFormat(&time);
    
    CPPUNIT_ASSERT(result == expected);
}

void ZipperUtilsTest::testParseTimeGivenANull()
{
    CPPUNIT_ASSERT(parseTimeToMSDosFormat(NULL) == 0);
}
