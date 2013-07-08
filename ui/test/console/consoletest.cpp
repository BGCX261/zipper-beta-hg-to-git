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

    remove("resources/test.zip");
}

void ConsoleTest::itShouldShowTheHelpWhenTheWrittenCommandIsHWithoutArgs()
{
    testTask(HELP_TEXT, 2, "./zipper", "-h");
}

void ConsoleTest::itShouldShowAnUnknowArgsErrorWhenTheWrittenCommandIsHWithArgs()
{
    testTask(UNKNOW_ARGS, 3, "./zipper", "-h", "dir1");
}

void ConsoleTest::itShouldShowAnUnknowCompressionArgsWhenTheWrittenCCommandIsWrong()
{
    testTask(UNKNOW_COMPRESSION_ARGS, 3, "./zipper", "-c", "src1");
}

void ConsoleTest::itShouldShowAnUnknowOptionWhenTheCommandDoesNotExists()
{
    testTask(UNKNOW_OPTION, 3, "./zipper", "-P", "src1");
}

void ConsoleTest::itShouldShowAnUnknowArgsErrorWhenTheInputCommandDoesNotMatch()
{
    testTask(UNKNOW_ARGS, 1, "./zipper");
}

void ConsoleTest::testTraverseOptionWithAnyParameter()
{
    testTask(UNKNOWN_TRAVERSE_ARGS, 2, "./zipper", "-t");
}

void ConsoleTest::testTraverseOptionWithANonZipFile()
{
    testTask(INVALID_ZIP_FILE_ERROR, 3, "./zipper", "-t", "resources/song.mp3");
}

void ConsoleTest::testTraverseOptionWithAFileThatDoNotExist()
{
    testTask(FILE_NOT_FOUND_ERROR, 3, "./zipper", "-t", "resources/somefile");
}

void ConsoleTest::testTraverseOptionWithAZipFile()
{
    testTask(OK_PROCESS, 3, "./zipper", "-t", "resources/severalFiles.zip");
}

void ConsoleTest::testTraverseOptionWithLevel()
{
    testTask(OK_PROCESS, 4, "./zipper", "-t", "resources/severalFiles.zip", "2");
}

void ConsoleTest::testTraverseOptionWithWrongLevel()
{
    testTask(UNKNOWN_TRAVERSE_ARGS, 4, "./zipper", "-t", "resources/severalFiles.zip", "lalala");
}

void ConsoleTest::testDecompressionOptionGivenAZipFile()
{
    testTask(OK_PROCESS, 4, "./zipper", "-d", "resources/severalFiles.zip", "resources");
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
    testTask(INVALID_ZIP_FILE_ERROR, 4, "./zipper", "-d", "resources/song.mp3", "resources");
}

void ConsoleTest::testDecompressionOptionGivenANonExistentFile()
{
    testTask(FILE_NOT_FOUND_ERROR,4, "./zipper", "-d", "resources/some.zip", "resources");
}

void ConsoleTest::testDecompressionOptionWithAnyParameter()
{
    testTask(UNKNOWN_DECOMPRESSION_ARGS, 2, "./zipper", "-d");
}

void ConsoleTest::testCompressOptionWithCompressionAlgorithm()
{
    testTask(OK_PROCESS, 5, "./zipper", "-c", "resources/song.mp3", "resources/test.zip", "12");
}

void ConsoleTest::testCompressOptionWithWrongCompressionAlgorithm()
{
    testTask(OK_PROCESS, 5, "./zipper", "-c", "resources/song.mp3", "resources/test.zip", "ae");
}

char** buildCommandArray(int commandsCount, va_list vl)
{
    char** res = new char *[commandsCount];
    int i;
    char* val;

    for (i = 0; i < commandsCount; i++)
    {
        val = va_arg(vl, char*);
        res[i] = new char[strlen(val) + 1];
        strcpy(res[i], val);
    }

    return res;
}

void testTask(const char* expectedOutput, int commandsCount, ...)
{
    va_list vl;
    va_start(vl, commandsCount);
    char** commands = buildCommandArray(commandsCount, vl);
    ConsoleZipper zipper(commandsCount, commands);
    const char* output = zipper.runCommand();
    CPPUNIT_ASSERT(strcmp(output, expectedOutput) == 0);
    va_end(vl);
    for (int i = 0; i < commandsCount; i++)
    {
        delete[] commands[i];
    }
    delete[] commands;
}