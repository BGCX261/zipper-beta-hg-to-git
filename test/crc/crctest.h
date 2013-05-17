/*
 * File:   utilstest.h
 * Author: luis
 *
 * Created on 15-05-2013, 06:02:51 PM
 */

#ifndef UTILSTEST_H
#define	UTILSTEST_H

#include <cppunit/extensions/HelperMacros.h>

class crctest : public CPPUNIT_NS::TestFixture 
{
    CPPUNIT_TEST_SUITE(crctest);

    CPPUNIT_TEST(testCrc32);
    CPPUNIT_TEST(testCrc32Size0);
    CPPUNIT_TEST(testCrc32Mp3File);
    CPPUNIT_TEST(testCrc32BinaryFile);

    CPPUNIT_TEST_SUITE_END();

public:
    crctest();
    virtual ~crctest();
    void setUp();
    void tearDown();

private:
    void testCrc32();
    void testCrc32Size0();
    void testCrc32Mp3File();
    void testCrc32BinaryFile();
    void openAndReadFile(const char* path);
};

#endif	/* UTILSTEST_H */

