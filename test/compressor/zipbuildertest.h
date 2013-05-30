/* 
 * File:   zipbuildertest.h
 * Author: kenji
 * Description: Test for zip builder
 * Created on May 23, 2013, 3:06 PM
 */

#include <cppunit/extensions/HelperMacros.h>
#include <string.h>
#include "../../src/compressor/zipbuilder.h"


#ifndef ZIPBUILDERTEST_H
#define	ZIPBUILDERTEST_H

class ZipBuilderTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(ZipBuilderTest);

    CPPUNIT_TEST(itShouldBuildTheZipFile);
    CPPUNIT_TEST(itShouldBuildTheZipFileWithAppropriateSize);
    //CPPUNIT_TEST(itShouldBuildTheZipFileWithTheCorrectContent);

    CPPUNIT_TEST_SUITE_END();

public:
    ZipBuilderTest();
    virtual ~ZipBuilderTest();
    void setUp();
    void tearDown();

private:
    /**
     * Test for the content of the zip file
     */
    void itShouldBuildTheZipFileWithTheCorrectContent();

    void itShouldBuildTheZipFileWithAppropriateSize();
    
    void itShouldBuildTheZipFile();
};

#endif	/* ZIPBUILDERTEST_H */

