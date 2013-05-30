#include "zipbuildertest.h"


CPPUNIT_TEST_SUITE_REGISTRATION(ZipBuilderTest);

ZipBuilder* builder;
fstream* outputstream;
char** input;

ZipBuilderTest::ZipBuilderTest()
{

}

ZipBuilderTest::~ZipBuilderTest()
{

}

void ZipBuilderTest::setUp()
{
    input = new char*[1];
}

void ZipBuilderTest::tearDown()
{
    delete builder;
    delete outputstream;
    delete[] input;
    builder = 0;
    outputstream = 0;
    input = 0;
}

void ZipBuilderTest::itShouldBuildTheZipFile()
{
    char* inputPath = (char*) "testrunner.cpp";
    input[0] = inputPath;
    builder = new ZipBuilder(input, 1, 0);
    outputstream = new fstream("compress.zip", std::fstream::out);
    builder->buildZipFile(outputstream);
    outputstream->close();
    FILE *fp = fopen("compress.zip", "r");
    CPPUNIT_ASSERT(fp);
    fclose(fp);
    remove("compress.zip");
}

void ZipBuilderTest::itShouldBuildTheZipFileWithAppropriateSize()
{
    char* inputPath = (char*) "testrunner.cpp";
    input[0] = inputPath;
    int expectedSize = 1152;
    builder = new ZipBuilder(input, 1, 0);
    outputstream = new fstream("compress.zip", std::fstream::out);
    builder->buildZipFile(outputstream);
    outputstream->close();
    FILE *fich;
    fich = fopen("compress.zip", "r");
    fseek(fich, 0L, SEEK_END);
    int actual = ftell(fich);
    fclose(fich);
    CPPUNIT_ASSERT(expectedSize == actual);
    remove("compess.zip");
}



