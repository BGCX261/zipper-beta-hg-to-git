/* 
 * File:   consolelib.h
 * Author: Kenji Lozano
 * Description: Define functions for the console library.
 *
 */

#ifndef CONSOLELIB_H
#define	CONSOLELIB_H
#include "zipper.h"


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
