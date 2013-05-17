#include "fileutils.h"
#include <sys/stat.h>

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