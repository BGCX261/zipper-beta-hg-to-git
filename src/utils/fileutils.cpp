#include "fileutils.h"
#include <dirent.h>
#include <sys/stat.h>
#include <string>
#include <string.h>
#include <utime.h>
#include <time.h>

/**
 * Check if the given path is not null and exist.
 * 
 * @param path Given path to check.
 */
void checkPath(const char* path) throw (FileNotFoundExpcetion, NullPathException, OpenFileException);

/**
 * Create a Path and search inside the path more files.
 * 
 * @param path Given path to search recursively.
 * @param files List where all the found files inside path will be added.
 */
void explorePath(const char* path, std::list<Path>& files) throw (FileException);

/**
 * Push the parent path into the list, then if the path is a diretory, explore the files inside that
 * directory to add them to the list. 
 * 
 * @param parent Path that contain the full and relative path of a file or directory.
 * @param list List where the found files will be added as Path structures.
 */
void listFiles(const Path& parent, std::list<Path> & list) throw (OpenFileException);

/**
 * Split the file name with / or \ and gets the last occurrence of that
 * 
 * @param str The string to split
 * @return The last occurrence
 */
std::string splitFileName(const std::string& str);


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

std::list<Path>* explorePaths(const char** paths, int pathsCount) throw (FileException)
{
    std::list<Path>* response = new std::list<Path>();

    for (int i = 0; i < pathsCount; i++)
    {
        explorePath(paths[i], *response);
    }

    return response;
}

void explorePath(const char* path, std::list<Path>& files)throw (FileException)
{
    checkPath(path);
    bool isDir = isDirectory(path);
    Path file(path, isDir);
    listFiles(file, files);
}

void checkPath(const char* path) throw (FileNotFoundExpcetion, NullPathException, OpenFileException)
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

void listFiles(const Path& parent, std::list<Path> & list) throw (OpenFileException)
{
    list.push_back(parent);

    if (!parent.isDir)
        return;

    DIR* directory = 0;
    struct dirent* entry = 0;

    if ((directory = opendir(parent.fullPath.c_str())) == NULL)
    {
        throw OpenFileException(parent.fullPath.c_str());
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

tm* recoverLastModificationDateAndTime(const char* path)
{
    if (!exist(path) || isDirectory(path))
    {
        return 0;
    }

    struct tm* tmModifiedTime;
    stat(path, &st_info);
    tmModifiedTime = gmtime(&(st_info.st_mtime));

    return tmModifiedTime;
}

std::string prepareTargetPath(const char* targetPath, const char* firstFileName)
{
    std::string strTargetPath(targetPath);
    if (strTargetPath.find(".zip") == std::string::npos)
    {
        std::string zipTarget;
        std::string zipFileName;
        std::string strFirstFile(firstFileName);
        zipFileName = splitFileName(strFirstFile);
        unsigned found = zipFileName.find_last_of(".");
        zipTarget = zipFileName.substr(0, found);
        if (*strTargetPath.rbegin() !='/')
            strTargetPath.append("/");

        strTargetPath.append(zipTarget);
        strTargetPath.append(".zip");
    }
    return strTargetPath;
}

std::string splitFileName(const std::string& str)
{
    unsigned found = str.find_last_of("/\\");
    std::string res = str.substr(found + 1);
    return res;
}

std::string getFileName(const std::string path)
{
    size_t found = path.find_last_of("/");
    return path.substr(found + 1);
}

bool setLastModificationDateAndTime(const char* path, tm* date) throw (FileException)
{
    if (!exist(path))
    {
        throw FileNotFoundExpcetion(path);
    }
    if (!date)
    {
        return false;
    }
    if (isDirectory(path))
    {
        return false;
    }
    struct utimbuf utimeBuffer;
    memset(&utimeBuffer, 0, sizeof (utimbuf));
    time(&utimeBuffer.actime);
    utimeBuffer.modtime = timegm(date);
    utime(path, &utimeBuffer);
    return true;
}

bool createADirectory(const char* path)
{
    if (!path)
    {
        return false;
    }

    if (exist(path))
    {
        return true;
    }

    mkdir(path, S_IRWXU | S_IRGRP | S_IXGRP);
    return true;
}
