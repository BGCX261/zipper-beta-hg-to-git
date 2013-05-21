/* 
 * File:   main.cpp
 * Author: Kenji Lozano
 * Description: The Main that recives the arguments to execute command
 *
 */

#include <cstdlib>
#include <stdio.h>
#include "consolelib.h"


using namespace std;

/**
 * Execute the command introduced by console
 * 
 * @param argc The number of arguments introduced by console
 * @param argv The arguments introduced by console
 * 
 * @return The error 
 */
int main(int argc, char** argv)
{

    const char* resp=executeCommand(argc,argv);
    printf("%s",resp);
    return 0;
    
}

