#include "zipbuilder.h"


ZipBuilder::ZipBuilder(char** input, int inputSize, int compressionMethod)
{
    this->inputPaths_ = 0;
    this->input_ = input;
    this->inputSize_ = inputSize;
    this->fileHeaders_ = new list<FileHeader*>();
    this->compressionMethod_ = compressionMethod;
    this->currentOffset_ = 0;
    this->cDirectoryOffset_ = 0;
}

ZipBuilder::ZipBuilder(const ZipBuilder& other)
{
    this->inputPaths_ = other.inputPaths_;
    this->fileHeaders_ = other.fileHeaders_;
    this->compressionMethod_ = other.compressionMethod_;
    this->currentOffset_ = other.currentOffset_;
    this->cDirectoryOffset_ = other.cDirectoryOffset_;
}

ZipBuilder::~ZipBuilder()
{
    if (this->fileHeaders_)
    {
        deleteFileHeaders();
        delete fileHeaders_;
    }
    if (this->inputPaths_)
        delete inputPaths_;
}

ErrorCode ZipBuilder::buildZipFile(iostream* outputStream)
{
    try
    {
        this->inputPaths_ = explorePaths((const char**) input_, inputSize_);

    } catch (FileNotFoundExpcetion)
    {
        return FILE_NOT_FOUND;
        
    } catch (NullPathException)
    {
        return INVALID_PARAMETERS;
        
    } catch (OpenFileException)
    {
        return CAN_NOT_OPEN_FILE;
    }
    buildFileHeaders(outputStream);
    list<FileHeader*>::iterator fHeaderIterator;
    this->cDirectoryOffset_ = currentOffset_;
    for (fHeaderIterator = fileHeaders_->begin(); fHeaderIterator != fileHeaders_->end(); fHeaderIterator++)
    {
        FileHeader* fileHeader = *fHeaderIterator;
        buildCentralDirectory(fileHeader, outputStream);
    }
    buildEndOfCentralDirectory(fileHeaders_->size(), outputStream);
    return OK;
}

void ZipBuilder::buildFileHeaders(iostream* outputStream)
{
    list<Path>::iterator pathIterator;

    for (pathIterator = inputPaths_->begin(); pathIterator != inputPaths_->end(); pathIterator++)
    {
        buildFileHeader(*pathIterator, outputStream);
    }
}

void ZipBuilder::buildFileHeader(const Path& path, iostream* outputStream)
{
    char* buffer = 0;
    FileHeader* fileHeader = createFileHeader(&path, compressionMethod_);
    buffer = new char[fileHeader->size()];

    fileHeader->offset = currentOffset_;
    currentOffset_ += fileHeader->size();

    getBuffer(fileHeader, buffer);
    outputStream->write(buffer, fileHeader->size());
    fileHeaders_->push_back(fileHeader);

    delete[] buffer;
}

void ZipBuilder::buildCentralDirectory(FileHeader* fileHeader, iostream* outputStream)
{
    int buffersize = C_DIRECTORY_PARTIAL_SIZE + fileHeader->fileNameLength;
    currentOffset_ += buffersize;
    int centralDirectorySignature = 0x02014b50;
    short version = 31;
    short commentLength = 0;
    short diskStart = 0;
    short internalAttribute = 0;
    int externalAtribute = 0;

    outputStream->write((char*) &centralDirectorySignature, sizeof (int));
    outputStream->write((char*) &version, sizeof (short));
    outputStream->write((char*) &fileHeader->versionToExtract, sizeof (short));
    outputStream->write((char*) &fileHeader->flag, sizeof (short));
    outputStream->write((char*) &fileHeader->compressionMethod, sizeof (short));
    outputStream->write((char*) &fileHeader->lastModificationTime, sizeof (short));
    outputStream->write((char*) &fileHeader->lastModificationDate, sizeof (short));
    outputStream->write((char*) &fileHeader->crc, sizeof (int));
    outputStream->write((char*) &fileHeader->compressedSize, sizeof (int));
    outputStream->write((char*) &fileHeader->unCompressedSize, sizeof (int));
    outputStream->write((char*) &fileHeader->fileNameLength, sizeof (short));
    outputStream->write((char*) &fileHeader->extraFieldLength, sizeof (short));
    outputStream->write((char*) &commentLength, sizeof (short));
    outputStream->write((char*) &diskStart, sizeof (short));
    outputStream->write((char*) &internalAttribute, sizeof (short));
    outputStream->write((char*) &externalAtribute, sizeof (int));
    outputStream->write((char*) &fileHeader->offset, sizeof (int));
    outputStream->write(fileHeader->fileName.c_str(), fileHeader->fileNameLength);
    outputStream->write((char*) fileHeader->extraField, fileHeader->extraFieldLength);

}

void ZipBuilder::buildEndOfCentralDirectory(int fHeaderCount, iostream* outputStream)
{
    int cDirectorySize = (currentOffset_ - cDirectoryOffset_);
    int endOfCentralDirectorySignature = 0x06054b50;
    short numberOfDisk = 0;
    short centralDirectoryStart = 0;
    short cDRecords = fHeaderCount;
    short numberOfCDRecords = fHeaderCount;
    short commentLength = 0;

    outputStream->write((char*) &endOfCentralDirectorySignature, sizeof (int));
    outputStream->write((char*) &numberOfDisk, sizeof (short));
    outputStream->write((char*) &centralDirectoryStart, sizeof (short));
    outputStream->write((char*) &cDRecords, sizeof (short));
    outputStream->write((char*) &numberOfCDRecords, sizeof (short));
    outputStream->write((char*) &cDirectorySize, sizeof (int));
    outputStream->write((char*) &cDirectoryOffset_, sizeof (int));
    outputStream->write((char*) &commentLength, sizeof (short));
}

void ZipBuilder::deleteFileHeaders()
{
    list<FileHeader*>::iterator fHeaderIterator;
    for (fHeaderIterator = fileHeaders_->begin(); fHeaderIterator != fileHeaders_->end(); fHeaderIterator++)
    {
        delete (*fHeaderIterator);
    }
}
