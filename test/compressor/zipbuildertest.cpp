#include "zipbuildertest.h"


CPPUNIT_TEST_SUITE_REGISTRATION(ZipBuilderTest);

using namespace std;

ZipBuilder* builder;
fstream* outputstream;
char** input;
ifstream* currentZipFile;
ifstream* expectedZipFile;

ZipBuilderTest::ZipBuilderTest()
{
    input = new char*[1];
    char* inputPath = (char*) "testrunner.cpp";
    input[0] = inputPath;
    std::list<Path>* inputPaths = explorePaths((const char**) input, 1);
    builder = new ZipBuilder(0);
    outputstream = new fstream("compress.zip", std::ios::out | std::ios::binary | std::ios::trunc);
    builder->buildZipFile(outputstream, inputPaths);
    outputstream->close();
    delete inputPaths;
    delete builder;
    delete outputstream;
    delete[] input;
}

ZipBuilderTest::~ZipBuilderTest()
{
    remove("compress.zip");
}

void ZipBuilderTest::setUp()
{
    currentZipFile = new ifstream("compress.zip", std::ifstream::in | std::ifstream::binary);
    expectedZipFile = new ifstream("resources/expectedCompress.zip", std::ifstream::in | std::ifstream::binary);

    currentZipFile->seekg(0, currentZipFile->end);
    expectedZipFile->seekg(0, expectedZipFile->end);
}

void ZipBuilderTest::tearDown()
{
    delete currentZipFile;
    delete expectedZipFile;
}

void ZipBuilderTest::testItShouldBuildTheZipFile()
{
    CPPUNIT_ASSERT(currentZipFile->good());
}

void ZipBuilderTest::testItShouldBuildTheZipFileWithAppropriateSize()
{
    int expectedSize = 1152;

    int actualSize = currentZipFile->tellg();

    CPPUNIT_ASSERT(expectedSize == actualSize);
}

void ZipBuilderTest::testItShouldBuildTheZipFileWithTheCorrectContent()
{
    int size = currentZipFile->tellg();

    currentZipFile->seekg(0, currentZipFile->beg);
    expectedZipFile->seekg(0, expectedZipFile->beg);

    char* currentData = new char[size];
    char* expectedData = new char[size];

    currentZipFile->read(currentData, size);
    expectedZipFile->read(expectedData, size);

    CPPUNIT_ASSERT(strcmp(currentData, expectedData) == 0);
}

void ZipBuilderTest::testItShouldBuildTheCentralDirectoryWithAppropriateSize()
{
    int cDirectoryOffset = 1070;
    char* cDirectorySignature = (char*) "0x02014b50";

    currentZipFile->seekg(0, currentZipFile->beg);
    currentZipFile->seekg(cDirectoryOffset, currentZipFile->beg);

    char* currentData = new char[4];
    currentZipFile->read(currentData, 4);

    CPPUNIT_ASSERT(strcmp(cDirectorySignature, currentData));
}

void ZipBuilderTest::testItShouldBuildTheCentralDirectoryWithTheCorrectContent()
{
    int cDirectoryOffset = 1070;
    int cDirectorySize = 60;

    currentZipFile->seekg(0, currentZipFile->beg);
    expectedZipFile->seekg(0, expectedZipFile->beg);

    char* currentDataZip = new char[cDirectorySize];
    char* expectedDataZip = new char[cDirectorySize];

    currentZipFile->seekg(cDirectoryOffset, currentZipFile->beg);
    expectedZipFile->seekg(cDirectoryOffset, expectedZipFile->beg);

    currentZipFile->read(currentDataZip, cDirectorySize);
    expectedZipFile->read(expectedDataZip, cDirectorySize);

    CPPUNIT_ASSERT(strcmp(currentDataZip, expectedDataZip) == 0);

}

void ZipBuilderTest::testItShouldBuildTheEndOfCentralDirectoryWithAppropriateSize()
{
    int endOfCDirectoryOffset = 1130;
    char* endOfCDirectorySignature = (char*) "0x06054b50";

    currentZipFile->seekg(0, currentZipFile->beg);
    currentZipFile->seekg(endOfCDirectoryOffset, currentZipFile->beg);

    char* currentData = new char[4];
    currentZipFile->read(currentData, 4);

    CPPUNIT_ASSERT(strcmp(endOfCDirectorySignature, currentData));
}

void ZipBuilderTest::testItShouldBuildTheEndOfCentralDirectoryWithTheCorrectContent()
{
    int endOfCDirectoryOffset = 1130;
    int endOfCDirectorySize = 22;

    currentZipFile->seekg(0, currentZipFile->beg);
    expectedZipFile->seekg(0, expectedZipFile->beg);

    char* currentDataZip = new char[endOfCDirectorySize];
    char* expectedDataZip = new char[endOfCDirectorySize];

    currentZipFile->seekg(endOfCDirectoryOffset, currentZipFile->beg);
    expectedZipFile->seekg(endOfCDirectoryOffset, expectedZipFile->beg);

    currentZipFile->read(currentDataZip, endOfCDirectorySize);
    expectedZipFile->read(expectedDataZip, endOfCDirectorySize);

    CPPUNIT_ASSERT(strcmp(currentDataZip, expectedDataZip) == 0);
}
