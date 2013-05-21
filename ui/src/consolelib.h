/* 
 * File:   consolelib.h
 * Author: Kenji Lozano
 * Description: The funtions for the library
 *
 */

#ifndef CONSOLELIB_H
#define	CONSOLELIB_H
#include "console/zipper.h"


/**
 * Execute the command introduced by console
 * 
 * @param argc The number of arguments introduced by console
 * @param argv The arguments introduced by console
 * 
 * @return The output errors for user
 */
const char* executeCommand(int argc, char** argv);

#endif	/* CONSOLELIB_H */
