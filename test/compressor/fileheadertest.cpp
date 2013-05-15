
/*
 * File:   FileHeaderTest.cpp
 * Author: Luis
 *
 * Created on 14-may-2013, 15:54:34
 */

#include <string.h>
#include <stdlib.h>
#include "fileheadertest.h"
#include "../../src/compressor/fileheader.h"


CPPUNIT_TEST_SUITE_REGISTRATION(FileHeaderTest);

FileHeader* header;

FileHeaderTest::FileHeaderTest()
{
}

FileHeaderTest::~FileHeaderTest()
{
}

void FileHeaderTest::setUp()
{
    header = new FileHeader();
}

void FileHeaderTest::tearDown()
{
    delete header;
    header = 0;
}

void FileHeaderTest::testStructure()
{

    header->fileName = "File1";
    header->versionToExtract = 10;
    header->compressionMethod = 0;
    header->flag = 10;
    header->crc = 123456;
    header->lastModificationTime = 34568;
    header->lastModificationDate = 24963;
    header->compressedSize = 12;
    header->unCompressedSize = 12;

    FileHeader fh2 = *header;

    CPPUNIT_ASSERT(*header == fh2);
    CPPUNIT_ASSERT(header->headerSignature == fh2.headerSignature);
    CPPUNIT_ASSERT(header->versionToExtract == fh2.versionToExtract);
    CPPUNIT_ASSERT(header->compressionMethod == fh2.compressionMethod);
    CPPUNIT_ASSERT(header->flag == fh2.flag);
    CPPUNIT_ASSERT(header->crc == fh2.crc);
    CPPUNIT_ASSERT(header->lastModificationTime == fh2.lastModificationTime);
    CPPUNIT_ASSERT(header->lastModificationDate == fh2.lastModificationDate);
    CPPUNIT_ASSERT(header->compressedSize == fh2.compressedSize);
    CPPUNIT_ASSERT(header->unCompressedSize == fh2.unCompressedSize);
}

void FileHeaderTest::testSetData()
{
    const char* data = "sample data";
    const int dataLength = strlen(data);
    header->setData(data, dataLength);
    CPPUNIT_ASSERT(memcmp(data, header->data, dataLength) == 0);
}

void FileHeaderTest::testSetExtraField()
{
    const char* field = "Field to compress";
    const int extraFieldLength = strlen(field);
    header->setExtraField(field, extraFieldLength);
    CPPUNIT_ASSERT(memcmp(field, header->extraField, extraFieldLength) == 0);
}
