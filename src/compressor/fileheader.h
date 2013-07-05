/* 
 * File:   FileHeader.h
 * Author: luis
 * Description: Represent's a file header following the zip structure and contain's 
 * functions to build a file header given a path of a file or directory. 
 * 
 * Created on 13 de mayo de 2013, 11:15 AM
 */

#ifndef FILEHEADER_H
#define	FILEHEADER_H
#include <string>
#include "../utils/path.h"
#include "../exceptions/unsupportedcompressionmethod.h"

#define FILE_HEADER_SIGNATURE  0x04034b50

struct FileHeader
{
    /**
     * Costructor.
     */
    FileHeader();
    
    /**
     * Constructor copy.
     * 
     * @param other Other FileHeader
     */
    FileHeader(const FileHeader& other);
    
    /**
     * Initialize with the values of the another FileHeader.
     * 
     * @param other Other FileHeader
     * @return The initialized FileHeader
     */
    FileHeader& operator=(const FileHeader& other);
    
    /**
     * To free memory used.
     */
    ~FileHeader();
    
    /**
     * Compare the names and return true if this are equals.
     * 
     * @param other Another file header
     * 
     * @return True if the names are equals
     */
    bool operator==(const FileHeader& other);
    
    /**
     * Local File header signature.
     */
    int headerSignature;
    
    /**
     * Version minimum needed to extract.
     */
    short versionToExtract;
    
    /**
     * General purpose bit flag.
     */
    short flag;
    
    /**
     * Compression method used on this file header.
     */
    short compressionMethod;
    
    /**
     * Last modification time of the file that represents this header.
     */
    short lastModificationTime;
    
    /**
     * Last modification date of the file that represents this header.
     */
    short lastModificationDate;
    
    /**
     * Value computed over file data by CRC-32 algorithm.
     */
    int crc;
    
    /**
     * Compressed size of the file .If is a directory this is 0.
     */
    int compressedSize;
    
    /**
     * Uncompressed size of the file. If is a directory this is 0.
     */
    int uncompressedSize;
    
    /**
     * Length of the file name.
     */
    short fileNameLength;
    
    /**
     * Length of the extra field.
     */
    short extraFieldLength;
    
    /**
     * Name of the file including an optional relative path.
     */
    std::string fileName;
    
    /**
     * Used to store additional information. The field consistes of a sequence 
     * of header and data pairs.
     */
    char* extraField;
    
    /**
     * Data of the file.
     */
    char* data;
    
    /**
     * Size of the data.
     */
    size_t dataSize;
    
    /**
     * offset of the file header in the file.
     */
    int offset;
    
    /**
     * Set the data.
     * 
     * @param data New value for the data
     * @param dataLength Length of the new data.
     */
    void setData(const char* data, const size_t dataLength, bool allocateMemory = true);
    
    /**
     * Set the extra field.
     * 
     * @param extraField New value for the extra field
     * @param extraFieldLength Length of the new extra field
     */
    void setExtraField(const char* extraField, const size_t extraFieldLength);
    
    /**
     * Calculate the size of the file header in bytes.
     * 
     * @return The size of the file header.
     */
    int size();
    
    /**
     * Compare all attributes of the file header with the other. If all attributes 
     * are equals return true
     * 
     * @param other Another file header
     * 
     * @return If all attributes of the file header are equals than the other
     */
    bool compare(const FileHeader& other);
    
private:
    /**
     * Initialize the attributes with the values of the anothoer file header.
     * 
     * @param other Other file header
     */
    void initialize(const FileHeader& other);
    
    /**
     * Initialize the attributes with default values.
     */
    void initialize();
    
    /**
     * To free memory used on this file header
     */
    void release();
};

/**
 * Create a file header given a Path.
 * 
 * @param path Path of the file
 * @param compressionMethod Compression Method that will be used to compress 
 * the file header.
 * 
 * @return The file header builded
 */
FileHeader* createFileHeader(const Path* path, const short compressionMethod) throw(UnsupportedCompressionMethod);

/**
 * Store all content of the file header in a buffer. The buffer must be free later.
 * 
 * @param fileHeader File header that will be stored in the buffer
 * @param buffer buffer where the file header will be stored
 */
void getBuffer(FileHeader* fileHeader, char*& buffer);

#endif	/* FILEHEADER_H */