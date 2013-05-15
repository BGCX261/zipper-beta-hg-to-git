#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "help.h"
#include "outputError.h"

#define DEFAULT_ARGS 2

#define COMPRESSION_ARGS 4

#define BEGIN_SOURCE_ARGS 2

#define OPTION_LENGTH 2

/**
 * Parse the error code from compressor
 * 0-Ok
 * 1-File not Found
 * 2-Compression not supported
 * 3-Corrupt File
 * @param errorCode The number of error Code
 */
void parseErrorCode(int errorCode)
{
    switch (errorCode)
    {
	case 1:
	    printf("%s", FILE_NOT_FOUND_ERROR);
	    break;
	case 2:
	    printf("%s", COMPRESSION_NOT_SUPPORTED_ERROR);
	    break;
	case 3:
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
char** getSourceCompressionArgs(char** argv, int end)
{
    int sizeArgs = end - BEGIN_SOURCE_ARGS;
    if (sizeArgs < 1)
    {
	printf("%s", ARGS_ERROR);
	return 0;
    }
    char** arguments = new char*[sizeArgs];
    int count = 0;
    for (int i = BEGIN_SOURCE_ARGS; i < end; i++)
    {
	arguments[count] = argv[i];
	count++;
    }
    return arguments;
}

/**
 * This is a False Compressor 
 */
int falseCompressor(char* output, char** input, int compressionMethod)
{
    printf("Compress Method:[%d]\n", compressionMethod);
    printf("Dest:[%s]\n", output);
    return 0;
}

/**
 * The compress Function that gets the source, destiny and compressionMethod arguments
 * @param argc The number of arguments introduced by console 
 * @param argv The arguments introduced by console
 */
void compress(int argc, char **argv)
{
    int endSourceArgs = argc - 2; //index that ends the source or input arguments
    int compressionMethod = argv[argc - 1][0] - '0'; // gets the number of compression method 
    char** sourcePaths = getSourceCompressionArgs(argv, endSourceArgs);
    int sourcePathsSize = endSourceArgs - BEGIN_SOURCE_ARGS;
    char* destPath = argv[endSourceArgs];
    if (sourcePaths)
    {
	int errorCode = falseCompressor(destPath, sourcePaths, compressionMethod);
	parseErrorCode(errorCode);
    }
    delete[] sourcePaths;
}

/**
 * The Help function that prints the help text to use the options
 */
void help()
{
    printf("%s\n", HELP_TEXT);
}

int main(int argc, char **argv)
{
    /**
     * The arguments are as follows
     * argv[0] the app name
     * argv[1] the option
     * from argv[2] to argv[argc-1] The arguments for the selected option
     *  
     */
    if (argc >= DEFAULT_ARGS)
    {
	char* option = argv[1]; //get the selected option
	char value = option[1]; //get the value of selected option
	if (strlen(option) == OPTION_LENGTH) //validate the option
	{
	    switch (value)
	    {
		case 'c':
		    compress(argc, argv);
		    break;
		case 'h':
		    help();
		    break;
		default:
		    printf("%s", OPTION_ERROR);
		    break;
	    }
	}
	else
	{
	    printf("%s", OPTION_ERROR);
	}
    }
    return 0;
}

