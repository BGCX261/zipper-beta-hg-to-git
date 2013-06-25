#include "consoletest.h"
#include <stdarg.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ConsoleTest);

ConsoleTest::ConsoleTest()
{
}

ConsoleTest::~ConsoleTest()
{
}

void ConsoleTest::setUp()
{
}

void ConsoleTest::tearDown()
{
    if (exist("resources/directorytest"))
    {
        remove("resources/directorytest/dir1/dir3/file2");
        rmdir("resources/directorytest/dir1/dir3");
        rmdir("resources/directorytest/dir1");
        remove("resources/directorytest/dir2/file3");
        rmdir("resources/directorytest/dir2");
        remove("resources/directorytest/file1");
        rmdir("resources/directorytest");
    }
}

void ConsoleTest::itShouldShowTheHelpWhenTheWrittenCommandIsHWithoutArgs()
{
    ConsoleZipper zipper(2, buildCommandArray(2, "./zipper", "-h"));
    const char* output = zipper.runCommand();
    CPPUNIT_ASSERT(strcmp(output, HELP_TEXT) == 0);
}

void ConsoleTest::itShouldShowAnUnknowArgsErrorWhenTheWrittenCommandIsHWithArgs()
{
    ConsoleZipper zipper(3, buildCommandArray(3, "./zipper", "-h", "dir1"));
    const char* output = zipper.runCommand();
    CPPUNIT_ASSERT(strcmp(output, UNKNOW_ARGS) == 0);
}

void ConsoleTest::itShouldShowAnUnknowCompressionArgsWhenTheWrittenCCommandIsWrong()
{
    ConsoleZipper zipper(3, buildCommandArray(3, "./zipper", "-c", "src1"));
    const char* output = zipper.runCommand();
    CPPUNIT_ASSERT(strcmp(output, UNKNOW_COMPRESSION_ARGS) == 0);
}

void ConsoleTest::itShouldShowAnUnknowOptionWhenTheCommandDoesNotExists()
{
    ConsoleZipper zipper(3, buildCommandArray(3, "./zipper", "-P", "src1"));
    const char* output = zipper.runCommand();
    CPPUNIT_ASSERT(strcmp(output, UNKNOW_OPTION) == 0);
}

void ConsoleTest::itShouldShowAnUnknowArgsErrorWhenTheInputCommandDoesNotMatch()
{
    ConsoleZipper zipper(1, buildCommandArray(1, "./zipper"));
    const char* output = zipper.runCommand();
    CPPUNIT_ASSERT(strcmp(output, UNKNOW_ARGS) == 0);
}

void ConsoleTest::testTraverseOptionWithAnyParameter()
{
    ConsoleZipper zipper(2, buildCommandArray(2, "./zipper", "-t"));
    const char* output = zipper.runCommand();
    CPPUNIT_ASSERT(strcmp(output, UNKNOWN_TRAVERSE_ARGS) == 0);
}

void ConsoleTest::testTraverseOptionWithANonZipFile()
{
    ConsoleZipper zipper(3, buildCommandArray(3, "./zipper", "-t", "resources/song.mp3"));
    const char* output = zipper.runCommand();
    CPPUNIT_ASSERT(strcmp(output, INVALID_ZIP_FILE_ERROR) == 0);
}

void ConsoleTest::testTraverseOptionWithAFileThatDoNotExist()
{
    ConsoleZipper zipper(3, buildCommandArray(3, "./zipper", "-t", "resources/somefile"));
    const char* output = zipper.runCommand();
    CPPUNIT_ASSERT(strcmp(output, FILE_NOT_FOUND_ERROR) == 0);
}

void ConsoleTest::testTraverseOptionWithAZipFile()
{
    ConsoleZipper zipper(3, buildCommandArray(3, "./zipper", "-t", "resources/severalFiles.zip"));
    const char* output = zipper.runCommand();
    CPPUNIT_ASSERT(strcmp(output, OK_PROCESS) == 0);
}

void ConsoleTest::testTraverseOptionWithLevel()
{
    ConsoleZipper zipper(4, buildCommandArray(4, "./zipper", "-t", "resources/severalFiles.zip", "2"));
    const char* output = zipper.runCommand();
    CPPUNIT_ASSERT(strcmp(output, OK_PROCESS) == 0);
}

void ConsoleTest::testTraverseOptionWithWrongLevel()
{
    ConsoleZipper zipper(4, buildCommandArray(4, "./zipper", "-t", "resources/severalFiles.zip", "lalala"));
    const char* output = zipper.runCommand();
    CPPUNIT_ASSERT(strcmp(output, UNKNOWN_TRAVERSE_ARGS) == 0);
}

void ConsoleTest::testDecompressionOptionGivenAZipFile()
{
    ConsoleZipper zipper(4, buildCommandArray(4, "./zipper", "-d", "resources/severalFiles.zip", "resources"));
    const char* output = zipper.runCommand();
    CPPUNIT_ASSERT(strcmp(output, OK_PROCESS) == 0);

    CPPUNIT_ASSERT(exist("resources/directorytest"));
    CPPUNIT_ASSERT(exist("resources/directorytest/dir1"));
    CPPUNIT_ASSERT(exist("resources/directorytest/dir1/dir3"));
    CPPUNIT_ASSERT(exist("resources/directorytest/dir1/dir3/file2"));
    CPPUNIT_ASSERT(exist("resources/directorytest/dir2"));
    CPPUNIT_ASSERT(exist("resources/directorytest/dir2/file3"));
    CPPUNIT_ASSERT(exist("resources/directorytest/file1"));
}

void ConsoleTest::testDecompressionOptionGivenANonZipFile()
{
    ConsoleZipper zipper(4, buildCommandArray(4, "./zipper", "-d", "resources/song.mp3", "resources"));
    const char* output = zipper.runCommand();
    CPPUNIT_ASSERT(strcmp(output, INVALID_ZIP_FILE_ERROR) == 0);
}

void ConsoleTest::testDecompressionOptionGivenANonExistentFile()
{
    ConsoleZipper zipper(4, buildCommandArray(4, "./zipper", "-d", "resources/some.zip", "resources"));
    const char* output = zipper.runCommand();
    CPPUNIT_ASSERT(strcmp(output, FILE_NOT_FOUND_ERROR) == 0);
}

void ConsoleTest::testDecompressionOptionWithAnyParameter()
{
    ConsoleZipper zipper(2, buildCommandArray(2, "./zipper", "-d"));
    const char* output = zipper.runCommand();
    CPPUNIT_ASSERT(strcmp(output, UNKNOWN_DECOMPRESSION_ARGS) == 0);
}

char** buildCommandArray(int commandsCount, ...)
{
    char** res = new char *[commandsCount];
    int i;
    char* val;
    va_list vl;
    va_start(vl, commandsCount);

    for (i = 0; i < commandsCount; i++)
    {
        val = va_arg(vl, char*);
        res[i] = new char[strlen(val)];
        strcpy(res[i], val);
    }
    
    va_end(vl);
    return res;
}