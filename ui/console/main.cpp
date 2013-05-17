/* 
 * File:   main.cpp
 * Author: Kenji
 *
 * Created on 16 de mayo de 2013, 18:41
 */

#include <cstdlib>
#include <stdio.h>

#include "zipper.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
{
    char* resp=ConsoleZipper::runCommand(argc,argv);
    printf("%s",resp);
    return 0;
}

