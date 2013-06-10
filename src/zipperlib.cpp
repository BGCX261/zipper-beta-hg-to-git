#include "zipperlib.h"
#include <ostream>
#include "utils/zipperutils.h"
#include "utils/fileutils.h"
#include "struct/tree.h"

ErrorCode compress(char* targetPath, char** inputfilePaths, int pathCount, int compressionMethod)
{
    return FILE_NOT_FOUND;
}

ErrorCode traverse(const char* zipPath)
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

        tree.list();
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
