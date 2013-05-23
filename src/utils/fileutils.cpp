#include "fileutils.h"
#include <dirent.h>
#include <sys/stat.h>
#include <string>
#include <string.h>

/**
 * Check if the given path is not null and exist.
 * 
 * @param path Given path to check.
 */
void checkPath(const char* path) throw (FileNotFoundExpcetion, NullPathException);

/**
 * Create a Path and search inside the path more files.
 * 
 * @param path Given path to search recursively.
 * @param files List where all the found files inside path will be added.
 */
void explorePath(const char* path, std::list<Path>& files) throw (FileNotFoundExpcetion, NullPathException);

/**
 * Push the parent path into the list, then if the path is a diretory, explore the files inside that
 * directory to add them to the list. 
 * 
 * @param parent Path that contain the full and relative path of a file or directory.
 * @param list List where the found files will be added as Path structures.
 */
void listFiles(const Path& parent, std::list<Path> & list);

struct stat st_info;

bool isFile(const char* path)
{
    if (exist(path))
    {
        return S_ISREG(st_info.st_mode);
    }

    return false;
}

bool isDirectory(const char* path)
{
    if (exist(path))
    {
        return S_ISDIR(st_info.st_mode);
    }

    return false;
}

bool exist(const char* path)
{
    if (path)
    {
        return (stat(path, &st_info) == 0);
    }

    return false;
}

std::list<Path>* explorePaths(const char** paths, int pathsCount) throw (FileNotFoundExpcetion, NullPathException)
{
    std::list<Path>* response = new std::list<Path>();

    for (int i = 0; i < pathsCount; i++)
    {
        explorePath(paths[i], *response);
    }

    return response;
}

void explorePath(const char* path, std::list<Path>& files)throw (FileNotFoundExpcetion, NullPathException)
{
    checkPath(path);
    bool isDir = isDirectory(path);
    Path file(path, isDir);
    listFiles(file, files);
}

void checkPath(const char* path) throw (FileNotFoundExpcetion, NullPathException)
{
    if (!path)
    {
        throw NullPathException();
    }
    if (!exist(path))
    {
        throw FileNotFoundExpcetion(path);
    }
}

void listFiles(const Path& parent, std::list<Path> & list)
{
    list.push_back(parent);

    if (!parent.isDir)
        return;
    
    DIR* directory = 0;
    struct dirent* entry = 0;

    if ((directory = opendir(parent.fullPath.c_str())) == NULL)
    {
        //TODO:log
        return;
    }

    while ((entry = readdir(directory)))
    {
        bool isNotCurrentOrParentDirectory = strncmp(entry->d_name, "..", 2) != 0 &&
                strncmp(entry->d_name, ".", 1) != 0;

        if (isNotCurrentOrParentDirectory)
        {
            bool isDir = entry->d_type == DT_DIR;
            Path path(parent, entry->d_name, isDir);
            listFiles(path, list);
        }
    }

    closedir(directory);
}
