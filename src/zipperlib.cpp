#include "zipperlib.h"
#include "compressor/zipbuilder.h"

ErrorCode compress(char* targetPath, char** inputfilePaths, int pathCount, int compressionMethod)
{
    std::fstream* stream = new std::fstream(targetPath, std::ios::out | std::ios::binary | std::ios::trunc);
    ZipBuilder* builder = new ZipBuilder(inputfilePaths, pathCount, compressionMethod);
    ErrorCode code = builder->buildZipFile(stream);
    stream->close();
    return code;
}
