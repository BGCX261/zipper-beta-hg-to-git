#include "fileutils.h"
#include <dirent.h>
#include <sys/stat.h>
#include <string>
#include <string.h>

void listFiles(std::string dirPath, std::string baseDir, std::list<Path> & list);

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

std::string getFileName(const std::string& path)
{
    size_t found = path.find_last_of("/\\");
    return path.substr(found + 1);
}

std::list<Path>* getFiles(const char** paths, int pathsCount) throw (FileNotFoundExpcetion, NullPathException)
{
    std::list<Path>* response = new std::list<Path>();

    for (int i = 0; i < pathsCount; i++)
    {
        if (paths[i])
        {
            if (exist(paths[i]))
            {
                bool isDir = isDirectory(paths[i]);
                std::string fullPath = paths[i];
                std::string relativePath = getFileName(fullPath);
                Path path(fullPath, relativePath, isDir);
                response->push_back(path);

                if (isDir)
                {
                    listFiles(path.fullPath, path.relativePath, *response);
                }
            }
            else
            {
                throw FileNotFoundExpcetion(paths[i]);
            }
        }
        else
        {
            throw NullPathException();
        }
    }

    return response;
}

/**
 * Inner method that add all the files in the dirPath to the given list.
 * 
 * @param fullPath Absolute path where the function will search files.
 * @param relativePath Relative path.
 * @param list List where the found files will be added as a Path struct.
 */
void listFiles(std::string fullPath, std::string relativePath, std::list<Path> & list)
{
    DIR* directory;
    struct dirent* entry;

    if ((directory = opendir(fullPath.c_str())) == NULL)
    {
        //TODO:log
        return;
    }

    while ((entry = readdir(directory)) != NULL)
    {
        if (strncmp(entry->d_name, "..", 2) != 0 && strncmp(entry->d_name, ".", 1) != 0)
        {
            bool isDir = entry->d_type == DT_DIR;
            Path path(fullPath, relativePath, entry->d_name, isDir);
            list.push_back(path);

            if (isDir)
            {
                listFiles(path.fullPath, path.relativePath, list);
            }
        }
    }

    closedir(directory);
}
