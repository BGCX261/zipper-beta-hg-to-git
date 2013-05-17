
#ifndef ZIPPER_H
#define	ZIPPER_H

#include "errorcode.h"
#include "zipperlib.h"
#include "outputerror.h"
#include "help.h"

#define DEFAULT_ARGS 2

#define COMPRESSION_ARGS 4

#define BEGIN_INDEX_SOURCE_ARGS 2

#define CONSOLE_OPTION_LENGTH 2

#define AMOUNT_COMPRESSION_ALGORITHMS 10

class ConsoleZipper
{
public:
    /**
     * Run the command introduced by console, running the command
     * @param argc The number of arguments introduced by console
     * @param argv The arguments introduced by console
     * @return The output errors for user
     */
    static char* runCommand(int argc, char** argv);
private:
    
    /**
     * Execute an specific command
     * @param option The name of command c(compression) h(help)
     * @param argc The number of arguments introduced by console
     * @param argv The arguments introduced by console
     * @return The output errors for user
     */
    static char* executeOption(char option, int argc, char** argv);

    /**
     *The compress Function that gets the source and destiny arguments
     * @param argc The number of arguments introduced by console 
     * @param argv The arguments introduced by console
     * @return The output errors for user
     */
    static char* compressOption(int argc, char** argv);

    /**
     * 
     * @param argc The parameters of the command
     * @return The help text for user
     */
    static char* helpOption(int argc);
    /**
     * Convert the error code from compressor to string
     * This codes are the following
     * 0-Ok
     * 1-File not Found
     * 2-Compression not supported
     * 3-Corrupt File
     * @param errorCode The number of error Code
     * @return The error code to String
     */
    static char* errorCodeToString(ErrorCode errorCode);

    /**
     * Get the Source Paths for compression
     * 
     * @param argv The input arguments from console
     * @param end The index where it ends the source paths
     * @return The source paths for compression
     */
    static char** getSourceCompressionArgs(char** argv, int end);


};


#endif	/* ZIPPER_H */

