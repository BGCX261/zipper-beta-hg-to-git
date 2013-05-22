/*
 * File:   FileUtilsTest.h
 * Author: Daniela Meneses
 * Description: Implement test for the methods that manage files.
 *
 * Created on May 16, 2013, 3:28:29 PM
 */

#ifndef FILEUTILSTEST_H
#define	FILEUTILSTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "utils/fileutils.h"

class FileUtilsTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(FileUtilsTest);

    CPPUNIT_TEST(testIsDirectoryWhenExist);
    CPPUNIT_TEST(testIsDirectoryWhenDoNotExist);
    CPPUNIT_TEST(testIsDirectoryGivenAFile);
    CPPUNIT_TEST(testIsDirectoryGivenANullParam);
    
    CPPUNIT_TEST(testIsFileWhenExist);
    CPPUNIT_TEST(testIsFileWhenDoNotExist);
    CPPUNIT_TEST(testIsFileGivenADirectory);
    CPPUNIT_TEST(testIsFileGivenANullParam);
    
    CPPUNIT_TEST(testExistWhenDoExist);
    CPPUNIT_TEST(testExistWhenDoNotExist);
    CPPUNIT_TEST(testExistWhenIsNull);
    
    CPPUNIT_TEST(testRecoverLastModiticationTDGivenAFile);
    CPPUNIT_TEST(testRecoverLastModificationTDGivenADirectory);
    CPPUNIT_TEST(testRecoverLastModificationTDWhenDoNotExist);

    CPPUNIT_TEST_SUITE_END();

public:
    FileUtilsTest();
    virtual ~FileUtilsTest();
    void setUp();
    void tearDown();

private:
    void testIsDirectoryWhenExist();
    void testIsDirectoryWhenDoNotExist();
    void testIsDirectoryGivenAFile();
    void testIsDirectoryGivenANullParam();
    
    void testIsFileWhenExist();
    void testIsFileWhenDoNotExist();
    void testIsFileGivenADirectory();
    void testIsFileGivenANullParam();
    
    void testExistWhenDoExist();
    void testExistWhenDoNotExist();
    void testExistWhenIsNull();
    
    void testRecoverLastModiticationTDGivenAFile();
    void testRecoverLastModificationTDGivenADirectory();
    void testRecoverLastModificationTDWhenDoNotExist();
};

#endif	/* FILEUTILSTEST_H */
