#ifndef CRC32_H
#define	CRC32_H

/**
 * Calculate the CRC-32 of bytes
 * 
 * @param bytes Bytes to calculate the CRC-32
 * 
 * @return Return the CRC-32 of the bytes
 */
unsigned int crc32(const char* buffer, int bufferSize);

#endif	/* CRC32_H */