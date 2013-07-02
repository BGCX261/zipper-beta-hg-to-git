/* 
 * File:   main.cpp
 * Author: Kenji Lozano
 * Description: Define the zipper console app for the user using the console library.
 *
 */

#include <cstdlib>
#include <stdio.h>
#include "consolelib.h"
#include "log/LoggerManager.h"
#include "log/FileLogger.h"

extern LoggerManager* g_logger;

using namespace std;

/**
 * Execute and shows the result status of the commands introduced in the console as 
 * parameters.
 * 
 * @param argc The number of arguments introduced by console.
 * @param argv The arguments introduced by console.
 */
int main(int argc, char** argv)
{
    g_logger->addFileLogger("ZipperLogs");
    const char* resp = executeCommand(argc, argv);
    printf("%s", resp);
    delete g_logger;
    return 0;
}

