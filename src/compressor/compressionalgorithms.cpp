#include "compressionalgorithms.h"
#include <bzlib.h>
#include <stdlib.h>

void evaluateBZResult(int result);

DataCompressedInfo bz2Compression(char* data, int dataSize) throw(CompressionAlgorithmException)
{
    DataCompressedInfo dataInfo;
    if (data)
    {
        // To guarantee that the compressed data will fit in its buffer.
        dataInfo.length = dataSize * 1.01 + 600; 
        dataInfo.data = (char*) malloc(dataInfo.length);
        int result = BZ2_bzBuffToBuffCompress(dataInfo.data, &dataInfo.length, data,
                dataSize, BLOCK_SIZE_100K, VERBOSITY, WORK_FACTOR);

        evaluateBZResult(result);
        
        if(result != BZ_OK)
        {
            throw CompressionAlgorithmException("Error compressing with bz2lib");
        }
    }

    return dataInfo;
}

DataCompressedInfo bz2Decompression(char* compressedData, unsigned int compressedDataSize, 
        int uncompressedDataSize) throw(CompressionAlgorithmException)
{
    DataCompressedInfo dataInfo;
    
    if(compressedData)
    {
        dataInfo.data = (char*) malloc(uncompressedDataSize);
        dataInfo.length = uncompressedDataSize;
        
        int result = BZ2_bzBuffToBuffDecompress(dataInfo.data, &dataInfo.length, compressedData, 
                compressedDataSize, SMALL, VERBOSITY);
        evaluateBZResult(result);
        
        if(result != BZ_OK)
        {
            throw CompressionAlgorithmException("Error compressing with bz2lib");
        }
    }
    
    return dataInfo;
}

void evaluateBZResult(int result)
{
    switch (result)
    {
        case BZ_CONFIG_ERROR:
            WARN("%s", "The bz library has not compiled");
            break;
        case BZ_PARAM_ERROR:
            WARN("%s", "Param error");
            break;
        case BZ_MEM_ERROR:
            WARN("%s", "Insufficient memory is available");
            break;
        case BZ_OUTBUFF_FULL:
            WARN("%s", "The size of the compressed data exceds *destLen");
            break;
        case(BZ_DATA_ERROR):
            WARN("%s", "The data integrity error was detected in the compressed data");
            break;
        case(BZ_DATA_ERROR_MAGIC):
            WARN("%s", "The compressed data doesn’t begin with the right magic bytes");
            break;
        case(BZ_UNEXPECTED_EOF):
            WARN("%s", "The compressed data ends unexpectedly");
            break;
        case BZ_OK:
            WARN("%s", "Ok");
            break;
    }
}