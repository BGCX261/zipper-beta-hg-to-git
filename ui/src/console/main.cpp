/* 
 * File:   main.cpp
 * Author: Kenji
 *
 * Created on 16 de mayo de 2013, 18:41
 */

#include <cstdlib>
#include <stdio.h>
#include "consolelib.h"


using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
{

    const char* resp=executeCommand(argc,argv);
    printf("%s",resp);
    return 0;
    
}

