
/*
 * File:   FileHeaderTest.cpp
 * Author: Luis
 *
 * Created on 14-may-2013, 15:54:34
 */

#include <string.h>
#include "fileheadertest.h"
#include "../../src/compressor/fileheader.h"


CPPUNIT_TEST_SUITE_REGISTRATION(FileHeaderTest);

FileHeader* fh;

FileHeaderTest::FileHeaderTest() {
}

FileHeaderTest::~FileHeaderTest() {
}

void FileHeaderTest::setUp() {
    fh = new FileHeader();
}

void FileHeaderTest::tearDown() {
    delete fh;
}

void FileHeaderTest::testStructure() {
    
    fh->fileName = "File1";
    fh->versionToExtract = 10;
    fh->compressionMethod = 0;
    fh->flag = 10;
    fh->crc = 123456;
    fh->lastModificationTime = 34568;
    fh->lastModificationDate = 24963;
    fh->compressedSize = 12;
    fh->unCompressedSize = 12;
    
    FileHeader fh2 = *fh;
    
    CPPUNIT_ASSERT(*fh == fh2);
    CPPUNIT_ASSERT(fh->headerSignature == fh2.headerSignature);
    CPPUNIT_ASSERT(fh->versionToExtract == fh2.versionToExtract);
    CPPUNIT_ASSERT(fh->compressionMethod == fh2.compressionMethod);
    CPPUNIT_ASSERT(fh->flag == fh2.flag);
    CPPUNIT_ASSERT(fh->crc == fh2.crc);
    CPPUNIT_ASSERT(fh->lastModificationTime == fh2.lastModificationTime);
    CPPUNIT_ASSERT(fh->lastModificationDate == fh2.lastModificationDate);
    CPPUNIT_ASSERT(fh->compressedSize == fh2.compressedSize);
    CPPUNIT_ASSERT(fh->unCompressedSize == fh2.unCompressedSize);
}

void FileHeaderTest::testSetData()
{
    const char* data = "sample data";
    fh->setData(data, 11);
    CPPUNIT_ASSERT(strcmp(data, fh->data) == 0);
}

void FileHeaderTest::testSetExtraField()
{
    const char* extraField = "Field to compress";
    fh->setExtraField(extraField, 17);
    CPPUNIT_ASSERT(strcmp(extraField, fh->extraField) == 0);
}
