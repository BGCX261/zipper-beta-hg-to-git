/*
 * File:   crctest.cpp
 * Author: Luis Aguirre
 * Description: Implementation of the test for the crc.
 *
 * Created on 15-05-2013, 06:02:51 PM
 */

#include <stdlib.h>
#include "crctest.h"
#include "utils/crc32.h"

CPPUNIT_TEST_SUITE_REGISTRATION(CRCTest);

char* buffer;
int size;

CRCTest::CRCTest()
{
}

CRCTest::~CRCTest()
{
}

void CRCTest::setUp()
{
    buffer = 0;
    size = 0;
}

void CRCTest::tearDown()
{
    if(buffer)
    {
        free(buffer);
        buffer = 0;
    }
}

void CRCTest::openAndReadFile(const char* path)
{
    FILE* file = fopen(path, "rb");
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);
    buffer = (char*) malloc(size);
    fread(buffer, sizeof(char), size, file);
}

void CRCTest::testCrc32()
{
    const char* buffer = "Crc-32 test";
    unsigned int expected = 0x39CFC63C;
    
    CPPUNIT_ASSERT(crc32(buffer, 11) == expected);
}

void CRCTest::testCrc32Size0()
{
    const char* buffer = "";
    unsigned int expected = 0;
    
    CPPUNIT_ASSERT(crc32(buffer, 0) == expected);
}

void CRCTest::testCrc32Mp3File()
{
    unsigned int expected = 0xA8436532;
    openAndReadFile("resources/song.mp3");
    
    CPPUNIT_ASSERT(crc32(buffer, size) == expected);
}

void CRCTest::testCrc32BinaryFile()
{
    unsigned int expected = 0x3F18C956;
    openAndReadFile("resources/binaryDoc.pdf");
    
    CPPUNIT_ASSERT(crc32(buffer, size) == expected);
}

