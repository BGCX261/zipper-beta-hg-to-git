#include "consolelib.h"

const char* executeCommand(int argc, char** argv)
{
    ConsoleZipper zipper(argc, argv);
    return zipper.runCommand();
}

