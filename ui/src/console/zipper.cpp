
#include "zipper.h"

const char* ConsoleZipper::runCommand(int argc, char** argv)
{
    if (argc >= DEFAULT_ARGS)
    {
        char* option = argv[1];
        char value = option[1];
        return (strlen(option) == 2) ? executeOption(value, argc, argv) : UNKNOW_OPTION;
    }
    else
    {
        return UNKNOW_ARGS;
    }
}

const char* ConsoleZipper::executeOption(char option, int argc, char** argv)
{
    switch (option)
    {
    case 'c':
        return compressOption(argc, argv);
        break;
    case 't':
        return traverseOption(argc, argv);
    case 'h':
        return helpOption(argc);
        break;
    default:
        return UNKNOW_OPTION;
        break;
    }

}

const char* ConsoleZipper::compressOption(int argc, char** argv)
{
    char* compressionNumberArgs = argv[argc - 1];
    int endSourceArgs = (strlen(compressionNumberArgs) > 1) ? (argc - 1) : (argc - 2);
    int compressionMethod = (strlen(compressionNumberArgs) == 1) ? atoi(compressionNumberArgs) : NOT_COMPRESSION_METHOD;
    char** sourcePaths = getSourceCompressionArgs(argv, endSourceArgs);
    int sourcePathsSize = endSourceArgs - BEGIN_INDEX_SOURCE_ARGS;
    char* destPath = argv[endSourceArgs];


    if (sourcePaths)
    {
        ErrorCode errorCode = (compressionMethod == NOT_COMPRESSION_METHOD) ? compress(destPath, sourcePaths, sourcePathsSize, 0) : compress(destPath, sourcePaths, sourcePathsSize, compressionMethod);
        delete[] sourcePaths;
        return errorCodeToString(errorCode);

    }
    else
    {
        return UNKNOW_COMPRESSION_ARGS;
    }

}

const char* ConsoleZipper::traverseOption(int argc, char** argv)
{
    if (argc != 3 && argc != 4)
    {
        return UNKNOWN_TRAVERSE_ARGS;
    }

    char* zipPath = argv[2];
    int level = argc == 4 ? atoi(argv[3]) : -1;
    if (level == 0) return UNKNOWN_TRAVERSE_ARGS;

    ErrorCode errorCode = traverse(zipPath, level);
    return errorCodeToString(errorCode);
}

const char* ConsoleZipper::helpOption(int argc)
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

const char* ConsoleZipper::errorCodeToString(ErrorCode errorCode)
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
    case CAN_NOT_OPEN_INPUT_FILE:
        return CAN_NOT_OPEN_ERROR;
        break;
    case CAN_NOT_FIND_TARGET_PATH:
        return CAN_NOT_FIND_TARGET_ERROR;
        break;
    case INVALID_PARAMETERS:
        return UNKNOW_ARGS;
        break;
    case INVALID_ZIP_FILE:
        return INVALID_ZIP_FILE_ERROR;
        break;
    default:
        return OK_PROCESS;
    }

}
