
#include "zipper.h"

ConsoleZipper::ConsoleZipper(int argumentsCount, char** arguments)
{
    this->result = OK;
    this->consoleError = 0;
    this->argumentsCount = argumentsCount;
    this->arguments = new char *[argumentsCount];
    for (int i = 0; i < argumentsCount; i++)
    {
        this->arguments[i] = new char[strlen(arguments[i]) + 1];
        strcpy(this->arguments[i], arguments[i]);
    }
}

ConsoleZipper::~ConsoleZipper()
{
    for (int i = 0; i < argumentsCount; i++)
    {
        delete this->arguments[i];
    }

    delete arguments;
}

const char* ConsoleZipper::runCommand()
{

    if (argumentsCount < DEFAULT_ARGS)
    {
        return UNKNOW_ARGS;
    }

    char* option = arguments[1];
    bool allowedCommandLength = strlen(option) == 2;

    if (!allowedCommandLength)
    {
        return UNKNOW_OPTION;
    }

    char value = option[1];
    executeOption(value);
    return (consoleError) ? consoleError : errorCodeToString();
}

void ConsoleZipper::executeOption(char option)
{
    switch (option)
    {
    case 'c':
        compressOption();
        break;
    case 't':
        traverseOption();
        break;
    case 'd':
        decompressOption();
        break;
    case 'h':
        helpOption();
        break;
    default:
        consoleError = UNKNOW_OPTION;
        break;
    }
}

void ConsoleZipper::compressOption()
{
    char* compressionNumberArgs = arguments[argumentsCount - 1];
    int endSourceArgs = (strlen(compressionNumberArgs) > 1) ? (argumentsCount - 1) : (argumentsCount - 2);
    int compressionMethod = (strlen(compressionNumberArgs) == 1) ? atoi(compressionNumberArgs) : NOT_COMPRESSION_METHOD;
    char** sourcePaths = getSourceCompressionArgs(endSourceArgs);
    int sourcePathsSize = endSourceArgs - BEGIN_INDEX_SOURCE_ARGS;
    char* destPath = arguments[endSourceArgs];

    if (!sourcePaths)
    {
        consoleError = UNKNOW_COMPRESSION_ARGS;
        return;
    }

    result = (compressionMethod == NOT_COMPRESSION_METHOD) ?
            compress(destPath, sourcePaths, sourcePathsSize, 0) :
            compress(destPath, sourcePaths, sourcePathsSize, compressionMethod);
    delete[] sourcePaths;
}

char** ConsoleZipper::getSourceCompressionArgs(int sourceArgsLimit)
{
    int sizeArgs = sourceArgsLimit - BEGIN_INDEX_SOURCE_ARGS;
    if (sizeArgs < 1)
    {
        return 0;
    }
    char** sourceArguments = new char*[sizeArgs];
    int count = 0;
    for (int i = BEGIN_INDEX_SOURCE_ARGS; i < sourceArgsLimit; i++)
    {
        sourceArguments[count] = arguments[i];
        count++;
    }
    return sourceArguments;
}

void ConsoleZipper::traverseOption()
{
    if (argumentsCount != 3 && argumentsCount != 4)
    {
        consoleError = UNKNOWN_TRAVERSE_ARGS;
        return;
    }

    char* zipPath = arguments[2];
    int level = argumentsCount == 4 ? atoi(arguments[3]) : -1;
    if (level == 0)
    {
        consoleError = UNKNOWN_TRAVERSE_ARGS;
        return;
    }

    result = traverse(zipPath, level);
}

void ConsoleZipper::decompressOption()
{
    if (argumentsCount != 4)
    {
        consoleError = UNKNOWN_DECOMPRESSION_ARGS;
        return;
    }

    char* zipPath = arguments[2];
    char* outputPath = arguments[3];
    result = decompress(zipPath, outputPath);
}

void ConsoleZipper::helpOption()
{
    consoleError = argumentsCount == DEFAULT_ARGS ? HELP_TEXT : UNKNOW_ARGS;
}

const char* ConsoleZipper::errorCodeToString()
{
    switch (result)
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
    case DECOMPRESS_FAIL:
        return DECOMPRESSION_ERROR;
        break;
    default:
        return OK_PROCESS;
    }
}
