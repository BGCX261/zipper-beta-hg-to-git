/* 
 * File:   compressionalgorithms.h
 * Author: Luis Aguirre
 * Description: Provide functions that uses algorithms to compress data
 *
 * Created on 28 de junio de 2013, 05:06 PM
 */

#ifndef COMPRESSIONALGORITHMS_H
#define	COMPRESSIONALGORITHMS_H

#include "../log/LoggerManager.h"
#include "../exceptions/compressionalgorithmexception.h"

#define BLOCK_SIZE_100K 6
#define VERBOSITY 0
#define WORK_FACTOR 100
#define SMALL 0

extern LoggerManager* g_logger;

struct DataCompressedInfo
{
    DataCompressedInfo(): data(0), length(0)
    {
    }
    
    char* data;
    unsigned int length;
};

/**
 * Uses the bz2lib library to compress the data and store the compressed data in buffer.
 * The buffer must to be released calling free() function
 * 
 * @param data Data that will be compressed
 * @param dataSize Data size
 * 
 * @return DataCompressedInfo structure with the compressed data and its length.
 */
DataCompressedInfo bz2Compression(char* data, int dataSize) throw(CompressionAlgorithmException);

/**
 * Uses the bz2lib library to decompress data in bzstream format and store the decompressed data 
 * in a buffer inside DataCompressedInfo. The buffer must to be released calling free() function
 * 
 * @param data Compressed data that will be decompresed
 * @param dataSize Compressed data size
 * 
 * @return DataCompressedInfo structure with the decompressed data and its length.
 */
DataCompressedInfo bz2Decompression(char* compressedData, unsigned int compressedDataSize, 
        int uncompressedDataSize) throw(CompressionAlgorithmException);

#endif	/* COMPRESSIONALGORITHMS_H */

