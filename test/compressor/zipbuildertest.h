/* 
 * File:   zipbuildertest.h
 * Author: Kenji Lozano
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

    CPPUNIT_TEST(testItShouldBuildTheZipFile);
    CPPUNIT_TEST(testItShouldBuildTheZipFileWithAppropriateSize);
    CPPUNIT_TEST(testItShouldBuildTheZipFileWithTheCorrectContent);
    CPPUNIT_TEST(testItShouldBuildTheCentralDirectoryWithAppropriateSize);
    CPPUNIT_TEST(testItShouldBuildTheEndOfCentralDirectoryWithTheCorrectContent);
    CPPUNIT_TEST(testItShouldBuildTheEndOfCentralDirectoryWithAppropriateSize);
    CPPUNIT_TEST(testItShouldBuildTheCentralDirectoryWithTheCorrectContent);

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
    void testItShouldBuildTheZipFile();

    void testItShouldBuildTheZipFileWithAppropriateSize();

    void testItShouldBuildTheZipFileWithTheCorrectContent();

    void testItShouldBuildTheCentralDirectoryWithAppropriateSize();

    void testItShouldBuildTheCentralDirectoryWithTheCorrectContent();

    void testItShouldBuildTheEndOfCentralDirectoryWithAppropriateSize();

    void testItShouldBuildTheEndOfCentralDirectoryWithTheCorrectContent();


};

#endif	/* ZIPBUILDERTEST_H */

