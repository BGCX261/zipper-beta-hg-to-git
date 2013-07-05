#include "compressionalgorithms.h"
#include <bzlib.h>
#include <stdlib.h>

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

        switch (result)
        {
            case BZ_CONFIG_ERROR:
                WARN("%s", "The bz library has not compiled");
                break;
            case BZ_PARAM_ERROR:
                WARN("%s", "param error");
                break;
            case BZ_MEM_ERROR:
                WARN("%s", "insufficient memory is available");
                break;
            case BZ_OUTBUFF_FULL:
                WARN("%s", "the size of the compressed data exceds *destLen");
                break;
            case BZ_OK:
                WARN("%s", "ok");
                break;
        }
        
        if(result != BZ_OK)
        {
            throw CompressionAlgorithmException("Error compressing with bz2lib");
        }
    }

    return dataInfo;
}
