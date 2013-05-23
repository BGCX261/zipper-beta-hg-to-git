/* 
 * File:   zipbuildertest.h
 * Author: kenji
 * Description: Test for zip builder
 * Created on May 23, 2013, 3:06 PM
 */

#include <cppunit/extensions/HelperMacros.h>

#ifndef ZIPBUILDERTEST_H
#define	ZIPBUILDERTEST_H



class ZipBuilderTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(ZipBuilderTest);

    CPPUNIT_TEST(itShouldAssembleTheZipFileWithTheCorrectContentSize);
    CPPUNIT_TEST(itShouldAssembleTheZipFileWithTheCorrectContent);

    CPPUNIT_TEST_SUITE_END();

public:
    ZipBuilderTest();
    virtual ~ZipBuilderTest();
    void setUp();
    void tearDown();

private:
    void itShouldAssembleTheZipFileWithTheCorrectContentSize();
    void itShouldAssembleTheZipFileWithTheCorrectContent();
};

#endif	/* ZIPBUILDERTEST_H */

