

#include "consoletest.h"

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
    if(exist("resources/directorytest"))
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
    char ** command = new char *[2];
    command[0] = "./zipper";
    command[1] = "-h";
    const char* output = ConsoleZipper::runCommand(2, command);
    CPPUNIT_ASSERT(strcmp(output, HELP_TEXT) == 0);
}

void ConsoleTest::itShouldShowAnUnknowArgsErrorWhenTheWrittenCommandIsHWithArgs()
{
    char ** command = new char *[3];
    command[0] = "./zipper";
    command[1] = "-h";
    command[2] = "dir1";
    const char* output = ConsoleZipper::runCommand(3, command);
    CPPUNIT_ASSERT(strcmp(output, UNKNOW_ARGS) == 0);
}

void ConsoleTest::itShouldShowAnUnknowCompressionArgsWhenTheWrittenCCommandIsWrong()
{
    char ** command = new char *[3];
    command[0] = "./zipper";
    command[1] = "-c";
    command[2] = "src1";
    const char* output = ConsoleZipper::runCommand(3, command);
    CPPUNIT_ASSERT(strcmp(output, UNKNOW_COMPRESSION_ARGS) == 0);

}

void ConsoleTest::itShouldShowAnUnknowOptionWhenTheCommandDoesNotExists()
{
    char ** command = new char *[3];
    command[0] = "./zipper";
    command[1] = "-P";
    command[2] = "src1";
    const char* output = ConsoleZipper::runCommand(3, command);
    CPPUNIT_ASSERT(strcmp(output, UNKNOW_OPTION) == 0);

}

void ConsoleTest::itShouldShowAnUnknowArgsErrorWhenTheInputCommandDoesNotMatch()
{
    char ** command = new char *[1];
    command[0] = "./zipper";
    const char* output = ConsoleZipper::runCommand(1, command);
    CPPUNIT_ASSERT(strcmp(output, UNKNOW_ARGS) == 0);

}

void ConsoleTest::testTraverseOptionWithAnyParameter()
{
    char ** command = new char *[2];
    command[0] = "./zipper";
    command[1] = "-t";
    const char* output = ConsoleZipper::runCommand(2, command);
    CPPUNIT_ASSERT(strcmp(output, UNKNOWN_TRAVERSE_ARGS) == 0);
}

void ConsoleTest::testTraverseOptionWithANonZipFile()
{
    char ** command = new char *[3];
    command[0] = "./zipper";
    command[1] = "-t";
    command[2] = "resources/song.mp3";
    const char* output = ConsoleZipper::runCommand(3, command);
    CPPUNIT_ASSERT(strcmp(output, INVALID_ZIP_FILE_ERROR) == 0);
}

void ConsoleTest::testTraverseOptionWithAFileThatDoNotExist()
{
    char ** command = new char *[3];
    command[0] = "./zipper";
    command[1] = "-t";
    command[2] = "resources/somefile";
    const char* output = ConsoleZipper::runCommand(3, command);
    CPPUNIT_ASSERT(strcmp(output, FILE_NOT_FOUND_ERROR) == 0);
}

void ConsoleTest::testTraverseOptionWithAZipFile()
{
    char ** command = new char *[3];
    command[0] = "./zipper";
    command[1] = "-t";
    command[2] = "resources/severalFiles.zip";
    const char* output = ConsoleZipper::runCommand(3, command);
    CPPUNIT_ASSERT(strcmp(output, OK_PROCESS) == 0);
}

void ConsoleTest::testTraverseOptionWithLevel()
{
    char ** command = new char *[4];
    command[0] = "./zipper";
    command[1] = "-t";
    command[2] = "resources/severalFiles.zip";
    command[3] = "2";
    const char* output = ConsoleZipper::runCommand(4, command);
    CPPUNIT_ASSERT(strcmp(output, OK_PROCESS) == 0);
}

void ConsoleTest::testTraverseOptionWithWrongLevel()
{
    char ** command = new char *[4];
    command[0] = "./zipper";
    command[1] = "-t";
    command[2] = "resources/severalFiles.zip";
    command[3] = "lalala";
    const char* output = ConsoleZipper::runCommand(4, command);
    CPPUNIT_ASSERT(strcmp(output, UNKNOWN_TRAVERSE_ARGS) == 0);
}

void ConsoleTest::testDecompressionOptionGivenAZipFile()
{
    char** const command = new char *[4];
    command[0] = "./zipper";
    command[1] = "-d";
    command[2] = "resources/severalFiles.zip";
    command[3] = "resources";
    const char* output = ConsoleZipper::runCommand(4, command);
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
    char** command = new char *[4];
    command[0] = "./zipper";
    command[1] = "-d";
    command[2] = "resources/song.mp3";
    command[3] = "resources";
    const char* output = ConsoleZipper::runCommand(4, command);
    CPPUNIT_ASSERT(strcmp(output, INVALID_ZIP_FILE_ERROR) == 0);
}

void ConsoleTest::testDecompressionOptionGivenANonExistentFile()
{
    char** command = new char *[4];
    command[0] = "./zipper";
    command[1] = "-d";
    command[2] = "resources/some.zip";
    command[3] = "resources";
    const char* output = ConsoleZipper::runCommand(4, command);
    CPPUNIT_ASSERT(strcmp(output, FILE_NOT_FOUND_ERROR) == 0);
}

void ConsoleTest::testDecompressionOptionWithAnyParameter()
{
    char** command = new char *[2];
    command[0] = "./zipper";
    command[1] = "-d";
    const char* output = ConsoleZipper::runCommand(2, command);
    CPPUNIT_ASSERT(strcmp(output, UNKNOWN_DECOMPRESSION_ARGS) == 0);
}
