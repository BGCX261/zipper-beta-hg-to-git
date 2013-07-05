/*
 * File:   AlgorithmsTest.h
 * Author: luis
 *
 * Created on 05-07-2013, 03:38:13 PM
 */

#ifndef ALGORITHMSTEST_H
#define	ALGORITHMSTEST_H

#include <cppunit/extensions/HelperMacros.h>

class AlgorithmsTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(AlgorithmsTest);

    CPPUNIT_TEST(testCompressAndDecompressAMp3FileWithBz2Lib);
    CPPUNIT_TEST(testCompressAndDecompressABinaryFileWithBz2lib);
    CPPUNIT_TEST(testCompressAndDecompressAEmptyDataWithBz2lib);
    
    CPPUNIT_TEST_SUITE_END();

public:
    AlgorithmsTest();
    virtual ~AlgorithmsTest();
    void setUp();
    void tearDown();

private:
    void testCompressAndDecompressAMp3FileWithBz2Lib();
    void testCompressAndDecompressABinaryFileWithBz2lib();
    void testCompressAndDecompressAEmptyDataWithBz2lib();
};

#endif	/* ALGORITHMSTEST_H */

