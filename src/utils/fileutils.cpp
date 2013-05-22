#include "fileutils.h"
#include <dirent.h>
#include <sys/stat.h>
#include <string>
#include <string.h>

void listFiles(const char* dirPath, std::string baseDir, std::list<Path> & list);

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
                std::string fullPath = paths[i];
                std::string name = getFileName(fullPath);

                if (isFile(paths[i]))
                {
                    Path path(fullPath, name);
                    response->push_back(path);
                }
                else
                {
                    name.append("/");
                    Path path(fullPath, name);
                    response->push_back(path);
                    listFiles(paths[i], name, *response);
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
 * @param dirPath Absolute path where the function will search files.
 * @param baseDir Relative path.
 * @param list List where the found files will be added as a Path struct.
 */
void listFiles(const char* dirPath, std::string baseDir, std::list<Path> & list)
{
    DIR* directory;
    struct dirent* entry;

    if ((directory = opendir(dirPath)) == NULL)
    {
        return;
    }

    while ((entry = readdir(directory)) != NULL)
    {
        if (strncmp(entry->d_name, "..", 2) != 0 && strncmp(entry->d_name, ".", 1) != 0)
        {
            std::string fullPath = dirPath;
            fullPath.append("/");
            fullPath.append(entry->d_name);
            std::string name = baseDir;
            name.append(entry->d_name);

            if (entry->d_type == DT_DIR)
            {
                name.append("/");
                Path path(fullPath, name);
                list.push_back(path);
                listFiles(fullPath.c_str(), name, list);
            }
            else
            {
                Path path(fullPath, name);
                list.push_back(path);
            }
        }
    }

    closedir(directory);
}
