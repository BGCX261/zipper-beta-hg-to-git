/* 
 * File:   zipper.h
 * Author: Kenji Lozano
 * Description: Run the command introduced by console validating the input arguments
 *
 */
#ifndef ZIPPER_H
#define	ZIPPER_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "errorcode.h"
#include "zipperlib.h"
#include "outputerror.h"
#include "help.h"

/**
 *This defines the necessary arguments to execute a command 
 */
#define DEFAULT_ARGS 2

/**
 *Identifying number that has not introduced a compression algorithm
 */
#define NOT_COMPRESSION_METHOD -1

/**
 *Necessary number of arguments for compress option
 */
#define COMPRESSION_ARGS 4

/**
 *The index that begins the source args of source args
 */
#define BEGIN_INDEX_SOURCE_ARGS 2

/**
 *The necessary length of console option
 */
#define CONSOLE_OPTION_LENGTH 2

/**
 * Runs the console commands introduced by console 
 */
class ConsoleZipper
{
public:
    /**
     * Run the command introduced by console
     * 
     * @param argc The number of arguments introduced by console
     * @param argv The arguments introduced by console
     * 
     * @return The output errors for user
     */
    static const char* runCommand(int argc, char** argv);
private:

    /**
     * Execute an specific command
     * 
     * @param option The name of command c(compression) h(help)
     * @param argc The number of arguments introduced by console
     * @param argv The arguments introduced by console
     * 
     * @return The output errors for user
     */
    static const char* executeOption(char option, int argc, char** argv);

    /**
     * The compress Function that gets the source and destiny arguments
     * 
     * @param argc The number of arguments introduced by console 
     * @param argv The arguments introduced by console
     * 
     * @return The output errors for user
     */
    static const char* compressOption(int argc, char** argv);

    /**
     * The traverse option that receive a zip file to traverse it and show it as a tree.
     * 
     * @param argc Arguments count
     * @param argv Arguments
     * 
     * @return Errors that occurred. 
     */
    static const char* traverseOption(int argc, char** argv);

    /**
     * Prints the help for user
     * 
     * @param argc The parameters of the command
     * 
     * @return The help text for user
     */
    static const char* helpOption(int argc);
    /**
     * Convert the error code from compressor to string
     * This codes are the following
     * 0-Ok
     * 1-File not Found
     * 2-Compression not supported
     * 3-Corrupt File
     * 
     * @param errorCode The number of error Code
     * 
     * @return The error code to String
     */
    static const char* errorCodeToString(ErrorCode errorCode);

    /**
     * Get the Source Paths for compression
     * 
     * @param argv The input arguments from console
     * @param end The index where it ends the source paths
     * 
     * @return The source paths for compression
     */
    static char** getSourceCompressionArgs(char** argv, int end);


};


#endif	/* ZIPPER_H */

