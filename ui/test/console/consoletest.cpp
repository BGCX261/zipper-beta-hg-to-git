
#include "consoletest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ConsoleTest);

ConsoleTest::ConsoleTest() { }

ConsoleTest::~ConsoleTest() { }

void ConsoleTest::setUp() { }

void ConsoleTest::tearDown() { }

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

