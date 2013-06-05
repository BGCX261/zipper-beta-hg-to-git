#include "zipperlib.h"

ErrorCode compress(char* targetPath, char** inputfilePaths, int pathCount, int compressionMethod)
{
    const char* zipName = checkTargetPath(targetPath, inputfilePaths[0]);
    std::fstream* stream = new std::fstream(zipName, std::ios::out | std::ios::binary | std::ios::trunc);
    ZipBuilder* builder = new ZipBuilder(inputfilePaths, pathCount, compressionMethod);
    ErrorCode code = builder->buildZipFile(stream);
    stream->close();
    return code;
}
