#include "zipbuilder.h"

using namespace std;

ZipBuilder::ZipBuilder(int compressionMethod)
{
    INFO("%s", "Creating a Zip Builder.");
    this->fileHeaders_ = new list<FileHeader*>();
    this->compressionMethod_ = compressionMethod;
    this->currentOffset_ = 0;
    this->cDirectoryOffset_ = 0;
}

ZipBuilder::ZipBuilder(const ZipBuilder& other)
{
    INFO("%s", "Creating a Zip Builder from another ZipBuilder.");
    this->fileHeaders_ = other.fileHeaders_;
    this->compressionMethod_ = other.compressionMethod_;
    this->currentOffset_ = other.currentOffset_;
    this->cDirectoryOffset_ = other.cDirectoryOffset_;
}

ZipBuilder::~ZipBuilder()
{
    INFO("%s", "Destroying the Zip Builder.");
    if (this->fileHeaders_)
    {
        deleteFileHeaders();
        delete fileHeaders_;
    }
}

void ZipBuilder::buildZipFile(iostream* outputStream,std::list<Path>* inputPaths)
{
    INFO("%s", "Star to build a zip file...");
    buildFileHeaders(outputStream,inputPaths);
    list<FileHeader*>::iterator fHeaderIterator;
    this->cDirectoryOffset_ = currentOffset_;
    for (fHeaderIterator = fileHeaders_->begin(); fHeaderIterator != fileHeaders_->end(); fHeaderIterator++)
    {
        FileHeader* fileHeader = *fHeaderIterator;
        buildCentralDirectory(fileHeader, outputStream);
    }
    buildEndOfCentralDirectory(fileHeaders_->size(), outputStream);
}

void ZipBuilder::buildFileHeaders(iostream* outputStream,std::list<Path>* inputPaths)
{
    INFO("%s", "Building file headers with the compiled files of the input path.");
    list<Path>::iterator pathIterator;

    for (pathIterator = inputPaths->begin(); pathIterator != inputPaths->end(); pathIterator++)
    {
        buildFileHeader(*pathIterator, outputStream);
    }
}

void ZipBuilder::buildFileHeader(const Path& path, iostream* outputStream)
{
    INFO("Building a file header for: %s", path.fullPath.c_str());
    char* buffer = 0;
    INFO("%s", "Creating the file header...");
    FileHeader* fileHeader = createFileHeader(&path, compressionMethod_);
    INFO("%s", "Setting the offset of the file header");
    fileHeader->offset = currentOffset_;
    currentOffset_ += fileHeader->size();
    INFO("%s", "Writing the file header in the stream.");
    getBuffer(fileHeader, buffer);
    outputStream->write(buffer, fileHeader->size());
    INFO("%s", "Adding the file header in to the list of created file headers.");
    fileHeaders_->push_back(fileHeader);

    free(buffer);
}

void ZipBuilder::buildCentralDirectory(FileHeader* fileHeader, iostream* outputStream)
{
    INFO("%s", "Building the central directory.");
    int buffersize = C_DIRECTORY_PARTIAL_SIZE + fileHeader->fileNameLength;
    currentOffset_ += buffersize;
    int centralDirectorySignature = CDIRECTORY_SIGNATURE;
    short version = CURRENT_VERSION;
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
    outputStream->write((char*) &fileHeader->uncompressedSize, sizeof (int));
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
    INFO("%s", "Building the end of the central directory.");
    int cDirectorySize = (currentOffset_ - cDirectoryOffset_);
    int endOfCentralDirectorySignature = END_CDIRECTORY_SIGNATURE;
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
