/*
 * File:   AlgorithmsTest.cpp
 * Author: luis
 *
 * Created on 05-07-2013, 03:38:14 PM
 */

#include "algorithmstest.h"
#include "algorithms/algorithms.h"
#include <string.h>
#include <stdlib.h>

CPPUNIT_TEST_SUITE_REGISTRATION(AlgorithmsTest);

AlgorithmsTest::AlgorithmsTest()
{
}

AlgorithmsTest::~AlgorithmsTest()
{
}

void AlgorithmsTest::setUp()
{
}

void AlgorithmsTest::tearDown()
{
}

void AlgorithmsTest::testCompressAndDecompressAMp3FileWithBz2Lib()
{
    FILE* file = fopen("resources/song.mp3", "rb");
    fseek(file, 0, SEEK_END);
    unsigned int fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* data = (char*) malloc(fileSize);
    fread(data, sizeof(char), fileSize, file);
    fclose(file);
    
    DataInfo compressedData = bz2Compression(data, fileSize);
    DataInfo uncompressedData = bz2Decompression(compressedData.data, compressedData.length, fileSize);
    
    CPPUNIT_ASSERT(fileSize == uncompressedData.length);
    CPPUNIT_ASSERT(memcmp(data, uncompressedData.data, fileSize) == 0);
}

void AlgorithmsTest::testCompressAndDecompressABinaryFileWithBz2lib()
{
    FILE* file = fopen("resources/binaryDoc.pdf", "rb");
    fseek(file, 0, SEEK_END);
    unsigned int fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* data = (char*) malloc(fileSize);
    fread(data, sizeof(char), fileSize, file);
    fclose(file);
    
    DataInfo compressedData = bz2Compression(data, fileSize);
    DataInfo uncompressedData = bz2Decompression(compressedData.data, compressedData.length, fileSize);
    
    CPPUNIT_ASSERT(fileSize == uncompressedData.length);
    CPPUNIT_ASSERT(memcmp(data, uncompressedData.data, fileSize) == 0);
}

void AlgorithmsTest::testCompressAndDecompressAEmptyDataWithBz2lib()
{
    char* data = (char*) "";
    unsigned int dataSize = strlen(data);
    DataInfo compressedData = bz2Compression(data, dataSize);
    DataInfo uncompressedData = bz2Decompression(compressedData.data, compressedData.length, dataSize);
    
    CPPUNIT_ASSERT(dataSize == uncompressedData.length);
    CPPUNIT_ASSERT(memcmp(data, uncompressedData.data, 0) == 0);
}

