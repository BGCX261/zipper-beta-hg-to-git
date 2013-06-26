/* 
 * File:   zipper.h
 * Author: Kenji Lozano
 * Description: Define a class to parser a console input parameters.
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
#include "log/LoggerManager.h"

extern LoggerManager* g_logger;

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
 * Parse a console input and use the zipper library to execute a task defined in the console paramenters. 
 */
class ConsoleZipper
{
public:

    ConsoleZipper(int argumentsCount, char**  arguments);
    ~ConsoleZipper();
    
    /**
     * Parse the parameters and run the command introduced by console.
     * 
     * @return The output errors for user if there is any.
     */
    const char* runCommand();
private:
    int argumentsCount;
    char** arguments;
    ErrorCode result;
    const char* consoleError;

    /**
     * Given an option decide which task will perform.
     * 
     * @param option The name of command c(compression) h(help) d(decompression) t(traverse)
     */
    void executeOption(char option);

    /**
     * The compress Function that gets the source and destiny arguments
     */
    void compressOption();

    /**
     * The traverse option that receive a zip file to traverse it and show it as a tree.     
     */
    void traverseOption();

    /**
     * The decompress option that receive a zip file and the destiny path where 
     * it will be decompressed.
     */
    void decompressOption();

    /**
     * Prints the help for user.
     */
    void helpOption();
    
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
    const char* errorCodeToString();

    /**
     * Get the Source Paths for compression
     * 
     * @param argv The input arguments from console
     * @param end The index where it ends the source paths
     * 
     * @return The source paths for compression
     */
    char** getSourceCompressionArgs(int boundary);
};


#endif	/* ZIPPER_H */

