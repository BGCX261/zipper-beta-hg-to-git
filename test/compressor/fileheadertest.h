/*
 * File:   FileHeaderTest.h
 * Author: Luis
 *
 * Created on 14-may-2013, 15:54:33
 */

#ifndef FILEHEADERTEST_H
#define	FILEHEADERTEST_H

#include <cppunit/extensions/HelperMacros.h>

class FileHeaderTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(FileHeaderTest);

    CPPUNIT_TEST(testStructure);
    CPPUNIT_TEST(testSetData);
    CPPUNIT_TEST(testSetExtraField);
    
    CPPUNIT_TEST(testCreateFileHeaderGivenAFile);
    CPPUNIT_TEST(testCreateFileHeaderGivenADirectory);
    CPPUNIT_TEST(testCreateFileHeaderGivenANull);
    
    CPPUNIT_TEST(testGetBufferGivenAFile);
    CPPUNIT_TEST(testGetBufferGivenADirectory);
    CPPUNIT_TEST(testGetBufferGivenANull);

    CPPUNIT_TEST_SUITE_END();

public:
    FileHeaderTest();
    virtual ~FileHeaderTest();
    void setUp();
    void tearDown();

private:
    void testStructure();
    void testSetData();
    void testSetExtraField();
    
    void testCreateFileHeaderGivenAFile();
    void testCreateFileHeaderGivenADirectory();
    void testCreateFileHeaderGivenANull();
    
    void testGetBufferGivenAFile();
    void testGetBufferGivenADirectory();
    void testGetBufferGivenANull();
};

#endif	/* FILEHEADERTEST_H */

