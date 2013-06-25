/*
 * File:   blowfishtest.h
 * Author: kenji
 *
 * Created on Jun 25, 2013, 4:29:31 AM
 */

#ifndef BLOWFISHTEST_H
#define	BLOWFISHTEST_H

#include <stdlib.h>
#include "../../src/encryption/blowfish.h"
#include <cppunit/extensions/HelperMacros.h>

class BlowfishTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(BlowfishTest);

    CPPUNIT_TEST(testBlowfishFeistel);

    CPPUNIT_TEST_SUITE_END();

public:
    BlowfishTest();
    virtual ~BlowfishTest();
    void setUp();
    void tearDown();

private:
    void testBlowfishFeistel();
};

#endif	/* BLOWFISHTEST_H */

