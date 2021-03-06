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
#include "utils/path.h"

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

    CPPUNIT_TEST(testListFilesFromADirectory);
    CPPUNIT_TEST(testListFilesFromManyDirectories);
    CPPUNIT_TEST(testListFilesWhenAFileDoesNotExist);
    CPPUNIT_TEST(testListFilesWhenAPathIsNull);
    CPPUNIT_TEST(testListFilesCheckNames);

    CPPUNIT_TEST(testGetFileName);
    CPPUNIT_TEST(testGetFileNameWhenItDoesnNotHaveASlash);
    CPPUNIT_TEST(testGetFileNameWhenIsEmpty);

    CPPUNIT_TEST(testRecoverLastModiticationTDGivenAFile);
    CPPUNIT_TEST(testRecoverLastModificationTDGivenADirectory);
    CPPUNIT_TEST(testRecoverLastModificationTDWhenDoNotExist);

    CPPUNIT_TEST(testCheckTargetPathWhenTheTargetPathIsValid);
    CPPUNIT_TEST(testCheckTargetPathWhenTheTargetPathIsInvalidAndTheOtherIsFile);
    CPPUNIT_TEST(testCheckTargetPathWhenTheTargetPathIsInvalidAndTheOtherIsDirectory);
    CPPUNIT_TEST(testCheckTargetPathWhenTheTargetDoesNotHaveTheLastSlashAndTheOtherIsFile);
    CPPUNIT_TEST(testCheckTargetPathWhenTheTargetDoesNotHaveTheLastSlashAndTheOtherIsDirectory);
    
    CPPUNIT_TEST(testSetLastModificationDateAndTimeGivenAFile);
    CPPUNIT_TEST(testSetLastModificationDateAndTimeGivenADirectory);
    CPPUNIT_TEST(testSetLastModificationDateAndTimeGivenANonExistentFile);
    CPPUNIT_TEST(testSetLastModificationDateAndTimeGivenANull);
    
    CPPUNIT_TEST(testCreateADirectory);
    CPPUNIT_TEST(testCreateADirectoryGivenAExistentDirectory);
    CPPUNIT_TEST(testCreateADirectoryGivenANull);
    
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

    void testListFilesFromADirectory();
    void testListFilesFromManyDirectories();
    void testListFilesWhenAFileDoesNotExist();
    void testListFilesWhenAPathIsNull();
    void testListFilesCheckNames();

    void testGetFileName();
    void testGetFileNameWhenItDoesnNotHaveASlash();
    void testGetFileNameWhenIsEmpty();

    void testRecoverLastModiticationTDGivenAFile();
    void testRecoverLastModificationTDGivenADirectory();
    void testRecoverLastModificationTDWhenDoNotExist();

    void testCheckTargetPathWhenTheTargetPathIsValid();
    void testCheckTargetPathWhenTheTargetPathIsInvalidAndTheOtherIsFile();
    void testCheckTargetPathWhenTheTargetPathIsInvalidAndTheOtherIsDirectory();
    void testCheckTargetPathWhenTheTargetDoesNotHaveTheLastSlashAndTheOtherIsFile();
    void testCheckTargetPathWhenTheTargetDoesNotHaveTheLastSlashAndTheOtherIsDirectory();
    
    void testSetLastModificationDateAndTimeGivenAFile();
    void testSetLastModificationDateAndTimeGivenADirectory();
    void testSetLastModificationDateAndTimeGivenANonExistentFile();
    void testSetLastModificationDateAndTimeGivenANull();
    
    void testCreateADirectory();
    void testCreateADirectoryGivenAExistentDirectory();
    void testCreateADirectoryGivenANull();
};

bool fileComparator(const Path& first, const Path& second);

#endif	/* FILEUTILSTEST_H */

