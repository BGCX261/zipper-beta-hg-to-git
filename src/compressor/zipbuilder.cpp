#include "zipbuilder.h"

ZipBuilder::ZipBuilder()
{
    this->buffer = 0;
    this->cDirectoryOffset = 0;
    this->endOfCDirectoryOffset = 0;
    this->bufferSize = 0;
}

ZipBuilder::ZipBuilder(const ZipBuilder& other)
{
    this->fileHeaders = other.fileHeaders;
    this->buffer = other.buffer;
    this->cDirectoryOffset = other.cDirectoryOffset;
    this->endOfCDirectoryOffset = other.endOfCDirectoryOffset;
    this->bufferSize = other.bufferSize;
}

ZipBuilder::~ZipBuilder()
{
    if (this->buffer)
    {
        free(this->buffer);
    }
}

void ZipBuilder::addFile(Path path)
{
    FileHeader* fileHeader = createFileHeader(path);
    this->bufferSize += C_DIRECTORY_PARTIAL_SIZE + fileHeader->fileNameLength;
    this->fileHeaders.push_back(*fileHeader);
}

char* ZipBuilder::getZipStructure()
{
    return this->buffer;
}

void ZipBuilder::buildFileHeaders()
{
    this->buffer = malloc(sizeof (char) * this->bufferSize);
    memset(buffer, 0, bufferSize);
    list<FileHeader>::iterator iter;
    int currentOffset = 0;
    for (iter = fileHeaders.begin(); iter != fileHeaders.end(); iter++)
    {
        conCat(buffer, (*iter).getBuffer(), currentOffset, (*iter).getBufferSize());
        currentOffset += (*iter).getBufferSize();
    }
}

void ZipBuilder::conCat(char*& buffer, const char* toCopy, size_t since, const size_t size)
{
    for (int i = 0; i < size; i++)
    {
        buffer[since] = toCopy[i];
        since++;
    }
}


