/*
 * File:   blowfishtest.cpp
 * Author: kenji
 *
 * Created on Jun 25, 2013, 4:29:32 AM
 */

#include <stdlib.h>

#include "blowfishtest.h"
#include "../../src/encryption/blowfish.h"


CPPUNIT_TEST_SUITE_REGISTRATION(BlowfishTest);

BlowfishTest::BlowfishTest()
{
}

BlowfishTest::~BlowfishTest()
{
}

void BlowfishTest::setUp()
{
}

void BlowfishTest::tearDown()
{
}

int32_t feistel(int32_t x)
{
    int8_t a, b, c, d;
    a = x >> 24;
    b = (x >> 16) & 0xff;
    c = (x >> 8) & 0xff;
    d = x & 0xff;
    int32_t h = SBox[0][a] + SBox[1][b];
    return ((h ^ SBox[2][c]) + SBox[3][d]);
}

void BlowfishTest::testBlowfishFeistel()
{
    for (int i = 0; i < BLOWFISH_ROUNDS + 2; i++)
    {
        int32_t data32 = (int32_t) PBox[0];
        int32_t expected = feistel(data32);
        Blowfish* blowfish = new Blowfish();
        int32_t actual = blowfish->blowfishFeistel(data32);
        CPPUNIT_ASSERT_EQUAL(actual, expected);
    }
}
