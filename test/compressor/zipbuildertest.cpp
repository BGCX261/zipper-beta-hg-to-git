#include "zipbuildertest.h"


CPPUNIT_TEST_SUITE_REGISTRATION(ZipBuilderTest);

ZipBuilder* builder;
stringstream* outputstream;

ZipBuilderTest::ZipBuilderTest() {

}

ZipBuilderTest::~ZipBuilderTest() {

}

void ZipBuilderTest::setUp() {
    outputstream = new stringstream();
}

void ZipBuilderTest::tearDown() {
    delete builder;
    delete outputstream;
    builder = 0;
    outputstream = 0;
}

void ZipBuilderTest::itShouldBuildTheZipFileWithTheCorrectContent() {
    char** input = new char*[1];
    input[0] = "";//location the file to be compressed
    builder = new ZipBuilder(input, 1, 0);
    builder->buildZipFile(outputstream);
    char* actual = outputstream->str();//actual zip file content
    char* expected = "";//expected zip file content
    CPPUNIT_ASSERT(strcmp(actual, expected) == 0);
}
