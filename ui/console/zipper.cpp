#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "help.h"
#include "outputerror.h"
#include "zipperlib.h"
#include "errorcode.h"

#define DEFAULT_ARGS 2

#define COMPRESSION_ARGS 4

#define BEGIN_INDEX_SOURCE_ARGS 2

#define CONSOLE_OPTION_LENGTH 2

#define AMOUNT_COMPRESSION_ALGORITHMS 10

/**
 * Convert the error code from compressor to string
 * 0-Ok
 * 1-File not Found
 * 2-Compression not supported
 * 3-Corrupt File
 * @param errorCode The number of error Code
 */
void errorCodeToString(ErrorCode errorCode) {
    switch (errorCode) {
        case FILE_NOT_FOUND:
            printf("%s", FILE_NOT_FOUND_ERROR);
            break;
        case UNSUPPORTED_COMPRESSION:
            printf("%s", COMPRESSION_NOT_SUPPORTED_ERROR);
            break;
        case CORRUPTED_FILE:
            printf("%s", CORRUPT_FILE_ERROR);
            break;
        default:
            printf("%s", OK_PROCESS);
            break;
    }

}

/**
 * Get the Source Paths for compression
 * 
 * @param argv The input arguments from console
 * @param end The index where it ends the source paths
 * @return The source paths
 */
char** getSourceCompressionArgs(char** argv, int end) {
    int sizeArgs = end - BEGIN_INDEX_SOURCE_ARGS;
    if (sizeArgs < 1) {
        printf("%s\n%s", ARGS_ERROR, COMPRESSION_DESCRIPTION);
        return 0;
    }
    char** arguments = new char*[sizeArgs];
    int count = 0;
    for (int i = BEGIN_INDEX_SOURCE_ARGS; i < end; i++) {
        arguments[count] = argv[i];
        count++;
    }
    return arguments;
}

/**
 * The compress Function that gets the source, destiny and compressionMethod arguments
 * @param argc The number of arguments introduced by console 
 * @param argv The arguments introduced by console
 */
void compressOption(int argc, char **argv) {
    int endSourceArgs = argc - 1; //index that ends the source or input arguments
    char** sourcePaths = getSourceCompressionArgs(argv, endSourceArgs);
    int sourcePathsSize = endSourceArgs - BEGIN_INDEX_SOURCE_ARGS;
    char* destPath = argv[endSourceArgs];
    if (sourcePaths) {
        ErrorCode errorCode = compress(destPath, sourcePaths, sourcePathsSize, 0);
        errorCodeToString(errorCode);
    }
    delete[] sourcePaths;
}

/**
 * The Help function that prints the help text to use the options
 */
void help() {
    printf("%s\n%s\n%s\n%s\n", APLICATION_DESCRIPTION, COMPRESSION_DESCRIPTION, COMPRESSION_EXAMPLE, HELP_DESCRIPTION);
}

int main(int argc, char **argv) {
    /**
     * The arguments are as follows
     * argv[0] the app name
     * argv[1] the option
     * from argv[2] to argv[argc-1] The arguments for the selected option
     *  
     */
    if (argc >= DEFAULT_ARGS) {
        char* option = argv[1]; //get the selected option
        char value = option[1]; //get the value of selected option
        if (strlen(option) == CONSOLE_OPTION_LENGTH) //validate the option
        {
            switch (value) {
                case 'c':
                    compressOption(argc, argv);
                    break;
                case 'h':
                    help();
                    break;
                default:
                    printf("%s", OPTION_ERROR);
                    help();
                    break;
            }
        } else {
            printf("%s", OPTION_ERROR);
            help();
        }

    } else {
        printf("%s\n", ARGS_ERROR);
        help();
    }
    return 0;
}

