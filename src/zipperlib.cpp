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
    std::list<Path>* inputPaths = 0;
    try
    {
        inputPaths = explorePaths((const char**) inputfilePaths, pathCount);

    }
    catch (FileNotFoundExpcetion& e)
    {
        ERROR("%s", e.what());
        return FILE_NOT_FOUND;
    }
    catch (NullPathException& e)
    {
        ERROR("%s", e.what());
        return INVALID_PARAMETERS;
    }
    catch (OpenFileException& e)
    {
        ERROR("%s", e.what());
        return CAN_NOT_OPEN_INPUT_FILE;
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
    delete inputPaths;
    INFO("%s", "Compression Successful");
    return OK;
}

ErrorCode traverse(const char* zipPath, int level)
{
    INFO("%s", "Traverse");
    try
    {
        std::list<FileHeader*> fileHeaders = navigate(zipPath);
        std::string filename = getFileName(zipPath);
        Tree tree(filename);
        for (std::list<FileHeader*>::iterator it = fileHeaders.begin(); it != fileHeaders.end(); it++)
        {
            FileHeader* fileHeader = *it;
            std::string file = fileHeader->fileName;
            tree.add(file);
        }

        tree.traverse(level);
    }
    catch (NullPathException ePath)
    {
        ERROR("%s", ePath.what());
        return INVALID_PARAMETERS;
    }
    catch (FileNotFoundExpcetion eFile)
    {
        ERROR("%s", eFile.what());
        return FILE_NOT_FOUND;
    }
    catch (NotZipFileException eZip)
    {
        ERROR("%s", eZip.what());
        return INVALID_ZIP_FILE;
    }

    INFO("%s", "Traverse Successful");
    return OK;
}

ErrorCode decompress(const char* zipPath, const char* outputPath)
{
    INFO("%s", "Decompressing");

    if (!zipPath || !outputPath || isFile(outputPath))
    {
        ERROR("%s", "Null parameters or they are not valid files.");
        return INVALID_PARAMETERS;
    }

    try
    {
        std::list<FileHeader*> fileHeaders;
        fileHeaders = navigate(zipPath);

        std::list<FileHeader*>::iterator it = fileHeaders.begin();
        for (; it != fileHeaders.end(); it++)
        {
            FileHeader* fileHeader = *it;
            decompressAFileHeader(fileHeader, outputPath);
            *it = 0;
            delete fileHeader;
        }
        fileHeaders.clear();
    }
    catch (FileNotFoundExpcetion e)
    {
        ERROR("%s", e.what());
        return FILE_NOT_FOUND;
    }
    catch (NotZipFileException e)
    {
        ERROR("%s", e.what());
        return INVALID_ZIP_FILE;
    }
    catch (UnsupportedCompressionMethod e)
    {
        ERROR("%s", e.what());
        return UNSUPPORTED_COMPRESSION;
    }
    catch (DecompressException e)
    {
        ERROR("%s", e.what());
        return DECOMPRESS_FAIL;
    }

    INFO("%s", "Decompress Successful");
    return OK;
}
