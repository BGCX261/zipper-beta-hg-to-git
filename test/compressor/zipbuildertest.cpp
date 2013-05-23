#include <string.h>

#include "../../src/compressor/zipbuilder.h"
#include "zipbuildertest.h"


CPPUNIT_TEST_SUITE_REGISTRATION(ZipBuilderTest);

ZipBuilder* builder;

ZipBuilderTest::ZipBuilderTest() {

}

ZipBuilderTest::~ZipBuilderTest() {

}

void ZipBuilderTest::setUp() {
    builder = new ZipBuilder();
    Path zipFilePath = new Path("algo", "algo");
    builder->addFile(zipFilePath);
}

void ZipBuilderTest::tearDown() {
    delete builder;
    builder = 0;
}

void ZipBuilderTest::itShouldAssembleTheZipFileWithTheCorrectContent() {
    builder->getZipStructure();
    int expectedZipFileSize = 0;
    int actualZipFileSize = builder->zipFileSize();
    CPPUNIT_ASSERT(expectedZipFileSize == actualZipFileSize);
}

void ZipBuilderTest::itShouldAssembleTheZipFileWithTheCorrectContentSize() {
    char* expectedBuffer = builder->getZipStructure();
    char* actualBuffer = 0;
    CPPUNIT_ASSERT(strcmp(expectedBuffer, actualBuffer) == 0);
}