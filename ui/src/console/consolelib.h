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
 * Receive a set of commands, parse them and execute the selected option.
 * 
 * @param argc The number of arguments introduced by console
 * @param argv The arguments introduced by console
 * 
 * @return The output error for the user if there is any.
 */
const char* executeCommand(int argc, char** argv);

#endif	/* CONSOLELIB_H */
