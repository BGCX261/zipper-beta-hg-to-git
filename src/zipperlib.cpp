#include "zipperlib.h"
#include <ostream>
#include "decompressor/decompressor.h"
#include "utils/fileutils.h"
#include "struct/tree.h"
#include "decompressor/decompressor.h"
#include "exceptions/decompressexception.h"
#include "exceptions/unsupportedcompressionmethod.h"
#include <list>

ErrorCode compress(char* targetPath, char** inputfilePaths, int pathCount, int compressionMethod)
{
    INFO("%s", "Compressing");
    std::list<Path> inputPaths;
    
    try
    {
        explorePaths((const char**) inputfilePaths, pathCount, inputPaths);
    }
    catch (ZipperException e)
    {
        ERROR("%s", e.what());
        return e.getErrorCode();
    }

    std::string zipName = prepareTargetPath(targetPath, inputfilePaths[0]);
    std::fstream* stream = new std::fstream(zipName.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);

    if (stream->fail())
    {
        ERROR("%d", "Failure at opening a stream.");
        return CAN_NOT_FIND_TARGET_PATH;
    }

    ZipBuilder* builder = new ZipBuilder(compressionMethod);
    builder->buildZipFile(stream, inputPaths);
    stream->close();
    delete builder;
    delete stream;
    INFO("%s", "Compression Successful");
    return OK;
}

ErrorCode traverse(const char* zipPath, int level)
{
    INFO("%s", "Traverse");
    ErrorCode result = OK;
    std::list<FileHeader*> fileHeaders;
    try
    {
        navigate(zipPath, fileHeaders);
        std::string filename = getFileName(zipPath);
        Tree tree(filename);
        for (std::list<FileHeader*>::iterator it = fileHeaders.begin(); it != fileHeaders.end(); it++)
        {
            FileHeader* fileHeader = *it;
            std::string file = fileHeader->fileName;
            tree.add(file);
        }

        tree.traverse(level);
        INFO("%s", "Traverse Successful");
    }
    catch (ZipperException e)
    {
        ERROR("%s", e.what());
        result = e.getErrorCode();
    }
    
    for (std::list<FileHeader*>::iterator it = fileHeaders.begin(); it != fileHeaders.end(); it++){
        delete *it;
    }
    fileHeaders.clear();

    return result;
}

ErrorCode decompress(const char* zipPath, const char* outputPath)
{
    INFO("%s", "Decompressing");
    ErrorCode res = OK;

    if (!zipPath || !outputPath || isFile(outputPath))
    {
        ERROR("%s", "Null parameters or they are not valid files.");
        return INVALID_PARAMETERS;
    }
    
    std::list<FileHeader*> fileHeaders;
    try
    {
        navigate(zipPath, fileHeaders);
        std::list<FileHeader*>::iterator it = fileHeaders.begin();
        for (; it != fileHeaders.end(); it++)
        {
            FileHeader* fileHeader = *it;
            decompressAFileHeader(fileHeader, outputPath);
        }
        INFO("%s", "Decompress Successful");
    }
    catch (ZipperException e)
    {
        ERROR("%s", e.what());
        res = e.getErrorCode();
    }

    std::list<FileHeader*>::iterator it = fileHeaders.begin();
    for (; it != fileHeaders.end(); it++)
    {
        delete *it;
    }

    fileHeaders.clear();
    return res;
}
