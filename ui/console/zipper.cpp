#include "zipper.h"
#include "outputerror.h"
#include "help.h"

char* ConsoleZipper::runCommand(int argc, char** argv)
{
    if (argc >= DEFAULT_ARGS)
    {
        char* option = argv[1];
        char value = option[1];
        return executeOption(value, argc, argv);
    }
    else
    {
        return UNKNOW_ARGS;
    }
}

char* ConsoleZipper::executeOption(char option, int argc, char** argv)
{
    switch (option)
    {
        case 'c':
            return compressOption(argc, argv);
            break;
        case 'h':
            return helpOption(argc);
            break;
        default:
            return UNKNOW_OPTION;
            break;
    }

}

char* ConsoleZipper::compressOption(int argc, char** argv)
{
    int endSourceArgs = argc - 1; //index that ends the source or input arguments
    char** sourcePaths = getSourceCompressionArgs(argv, endSourceArgs);
    int sourcePathsSize = endSourceArgs - BEGIN_INDEX_SOURCE_ARGS;
    char* destPath = argv[endSourceArgs];
    if (sourcePaths)
    {
        ErrorCode errorCode = compress(destPath, sourcePaths, sourcePathsSize, 0);
        delete[] sourcePaths;
        return errorCodeToString(errorCode);

    }
    else
    {
        return UNKNOW_COMPRESSION_ARGS;
    }

}

char* ConsoleZipper::helpOption(int argc)
{
    if (argc == DEFAULT_ARGS)
        return HELP_TEXT;
    return UNKNOW_ARGS;
}

char** ConsoleZipper::getSourceCompressionArgs(char** argv, int end)
{
    int sizeArgs = end - BEGIN_INDEX_SOURCE_ARGS;
    if (sizeArgs < 1)
    {
        return 0;
    }
    char** arguments = new char*[sizeArgs];
    int count = 0;
    for (int i = BEGIN_INDEX_SOURCE_ARGS; i < end; i++)
    {
        arguments[count] = argv[i];
        count++;
    }
    return arguments;
}

char* ConsoleZipper::errorCodeToString(ErrorCode errorCode)
{
    switch (errorCode)
    {
        case FILE_NOT_FOUND:
            return FILE_NOT_FOUND_ERROR;
            break;
        case UNSUPPORTED_COMPRESSION:
            return COMPRESSION_NOT_SUPPORTED_ERROR;
            break;
        case CORRUPTED_FILE:
            return CORRUPT_FILE_ERROR;
            break;
        default:
            return OK_PROCESS;
            break;
    }

}
