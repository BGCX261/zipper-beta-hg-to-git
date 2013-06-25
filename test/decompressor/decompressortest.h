/*
 * File:   decompressortest.h
 * Author: Luis Aguirre
 * Description: Test the decompression functions.
 *
 * Created on 05-06-2013, 04:27:22 PM
 */

#ifndef DECOMPRESSORTEST_H
#define	DECOMPRESSORTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "decompressor/decompressor.h"

class DecompressorTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(DecompressorTest);

    CPPUNIT_TEST(testNavigateGivenAZipWithOneFile);
    CPPUNIT_TEST(testNavigateGivenAZipWithSeveralFiles);
    CPPUNIT_TEST(testNavigateGivenANonZipFile);
    CPPUNIT_TEST(testNavigateGivenANonExistentFile);
    
    CPPUNIT_TEST(testDecompressAFileHeaderGivenAFile);
    CPPUNIT_TEST(testDecompressAFileHeaderGivenADirectory);
    CPPUNIT_TEST(testDecompressAFileHeaderGivenANull);
    
    CPPUNIT_TEST(testLastModificationTimeOfADecompressedFile);

    CPPUNIT_TEST_SUITE_END();

public:
    DecompressorTest();
    virtual ~DecompressorTest();
    void setUp();
    void tearDown();

private:
    
    void testNavigateGivenAZipWithOneFile();
    void testNavigateGivenAZipWithSeveralFiles();
    void testNavigateGivenANonZipFile();
    void testNavigateGivenANonExistentFile();
    
    void testDecompressAFileHeaderGivenAFile();
    void testDecompressAFileHeaderGivenADirectory();
    void testDecompressAFileHeaderGivenANull();
    
    void testLastModificationTimeOfADecompressedFile();
};

#endif	/* DECOMPRESSORTEST_H */

