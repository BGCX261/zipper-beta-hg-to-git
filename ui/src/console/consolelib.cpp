#include "consolelib.h"

const char* executeCommand(int argc, char** argv)
{
    return ConsoleZipper::runCommand(argc, argv);
}

