#include "zipperlib.h"
#include <ostream>
#include "decompressor/decompressor.h"
#include "utils/fileutils.h"
#include "struct/tree.h"

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

ErrorCode traverse(const char* zipPath, int level)
{
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
        return INVALID_PARAMETERS;
    }
    catch (FileNotFoundExpcetion eFile)
    {
        return FILE_NOT_FOUND;
    }
    catch (NotZipFileException eZip)
    {
        return INVALID_ZIP_FILE;
    }

    return OK;
}
