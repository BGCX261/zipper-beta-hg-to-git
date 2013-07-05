/*
 * File:   dateconvertertest.cpp
 * Author: luis
 *
 * Created on 07-06-2013, 07:02:50 PM
 */

#include "dateconvertertest.h"
#include <string.h>


CPPUNIT_TEST_SUITE_REGISTRATION(DateConverterTest);

DateConverterTest::DateConverterTest()
{
}

DateConverterTest::~DateConverterTest()
{
}

void DateConverterTest::setUp()
{
}

void DateConverterTest::tearDown()
{
}

void DateConverterTest::testParseDate()
{
    struct tm date;
    memset(&date, 0, sizeof (tm));
    date.tm_year = 2011 - 1900; //Following the tm structure
    date.tm_mon = 6 - 1; //Following the tm structure
    date.tm_mday = 29;
    short expected = 16093;
    DateConverter* converter = new DateConverter();
    short result = converter->parseDateToMSDosFormat(&date);

    CPPUNIT_ASSERT(result == expected);
    delete converter;
}

void DateConverterTest::testParseDate2()
{
    struct tm date;
    memset(&date, 0, sizeof (tm));
    date.tm_year = 2013 - 1900; //Following the tm structure
    date.tm_mon = 2 - 1; //Following the tm structure
    date.tm_mday = 4;
    short expected = 16964;
    DateConverter* converter = new DateConverter();
    short result = converter->parseDateToMSDosFormat(&date);

    CPPUNIT_ASSERT(result == expected);
    delete converter;
}

void DateConverterTest::testParseDateGivenValuesInZero()
{
    struct tm date;
    memset(&date, 0, sizeof (tm));
    date.tm_year = 0 - 1900; //Following the tm structure
    date.tm_mon = 0 - 1; //Following the tm structure
    date.tm_mday = 0;
    short expected = 0;
    DateConverter* converter = new DateConverter();
    short result = converter->parseDateToMSDosFormat(&date);

    CPPUNIT_ASSERT(result == expected);
    delete converter;
}

void DateConverterTest::testParseDateGivenANull()
{
    DateConverter* converter = new DateConverter();

    CPPUNIT_ASSERT(converter->parseDateToMSDosFormat(NULL) == 0);
    delete converter;
}

void DateConverterTest::testParseTime()
{
    struct tm time;
    memset(&time, 0, sizeof (tm));
    time.tm_hour = 11;
    time.tm_min = 30;
    time.tm_sec = 8;
    short expected = 23492;
    DateConverter* converter = new DateConverter();
    short result = converter->parseTimeToMSDosFormat(&time);

    CPPUNIT_ASSERT(result == expected);
    delete converter;
}

void DateConverterTest::testParseTime2()
{
    struct tm time;
    memset(&time, 0, sizeof (tm));
    time.tm_hour = 22;
    time.tm_min = 12;
    time.tm_sec = 20;
    short expected = 45450;
    DateConverter* converter = new DateConverter();
    short result = converter->parseTimeToMSDosFormat(&time);

    CPPUNIT_ASSERT(result == expected);
    delete converter;
}

void DateConverterTest::testParseTimeGivenValuesInZero()
{
    struct tm time;
    memset(&time, 0, sizeof (tm));
    time.tm_hour = 0;
    time.tm_min = 0;
    time.tm_sec = 0;
    short expected = 0;
    DateConverter* converter = new DateConverter();
    short result = converter->parseTimeToMSDosFormat(&time);

    CPPUNIT_ASSERT(result == expected);
    delete converter;
}

void DateConverterTest::testParseTimeGivenANull()
{
    DateConverter* converter = new DateConverter();

    CPPUNIT_ASSERT(converter->parseTimeToMSDosFormat(NULL) == 0);
    delete converter;
}

void DateConverterTest::testParseMSDosToTm()
{
    const short date = 16093;
    const short time = 23492;
    DateConverter* converter = new DateConverter();
    tm result;
    memset(&result, 0, sizeof (tm));
    converter->parseMSDosToTm(date, time, &result);

    CPPUNIT_ASSERT(result.tm_year == 2011 - 1900);
    CPPUNIT_ASSERT(result.tm_mon == 5);
    CPPUNIT_ASSERT(result.tm_mday == 29);
    CPPUNIT_ASSERT(result.tm_hour == 11);
    CPPUNIT_ASSERT(result.tm_min == 30);
    CPPUNIT_ASSERT(result.tm_sec == 8);
    delete converter;
}

