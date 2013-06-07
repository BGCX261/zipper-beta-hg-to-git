#include "zipperlib.h"

ErrorCode compress(char* targetPath, char** inputfilePaths, int pathCount, int compressionMethod)
{
    std::list<Path>* inputPaths = 0;
    try
    {
        inputPaths = explorePaths((const char**) inputfilePaths, pathCount);

    } catch (FileNotFoundExpcetion& e)
    {
        return FILE_NOT_FOUND;

    } catch (NullPathException& e)
    {
        return INVALID_PARAMETERS;

    } catch (OpenFileException& e)
    {
        return CAN_NOT_OPEN_INPUT_FILE;
    }
    std::string zipName = prepareTargetPath(targetPath, inputfilePaths[0]);
    std::fstream* stream = new std::fstream(zipName.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);
    if (stream->fail())
    {
        return CAN_NOT_FIND_TARGET_PATH;
    }
    ZipBuilder* builder = new ZipBuilder(compressionMethod);
    builder->buildZipFile(stream,inputPaths);
    stream->close();
    delete builder;
    delete stream;
    delete inputPaths;
    return OK;
}
