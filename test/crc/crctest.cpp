/*
 * File:   utilstest.cpp
 * Author: luis
 *
 * Created on 15-05-2013, 06:02:51 PM
 */

#include <stdlib.h>
#include <dirent.h>
#include "crctest.h"
#include "../../src/utils/crc32.h"

CPPUNIT_TEST_SUITE_REGISTRATION(crctest);

char* buffer;
int size;

crctest::crctest()
{
}

crctest::~crctest()
{
}

void crctest::setUp()
{
    buffer = 0;
    size = 0;
}

void crctest::tearDown()
{
    if(buffer)
    {
        free(buffer);
        buffer = 0;
    }
}

void crctest::openAndReadFile(const char* path)
{
    FILE* file = fopen(path, "rb");
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);
    buffer = (char*) malloc(size);
    fread(buffer, sizeof(char), size, file);
}

void crctest::testCrc32()
{
    const char* buffer = "Crc-32 test";
    unsigned int expected = 0x39CFC63C;
    
    CPPUNIT_ASSERT(crc32(buffer, 11) == expected);
}

void crctest::testCrc32Size0()
{
    const char* buffer = "";
    unsigned int expected = 0;
    
    CPPUNIT_ASSERT(crc32(buffer, 0) == expected);
}

void crctest::testCrc32Mp3File()
{
    unsigned int expected = 0xA8436532;
    openAndReadFile("files/song.mp3");
    
    CPPUNIT_ASSERT(crc32(buffer, size) == expected);
}

void crctest::testCrc32BinaryFile()
{
    unsigned int expected = 0x3F18C956;
    openAndReadFile("files/binaryDoc.pdf");
    
    CPPUNIT_ASSERT(crc32(buffer, size) == expected);
}

