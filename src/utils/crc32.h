/* 
 * File:   crc32.h
 * Author: luis
 * Description: Provide the function to calculate the crc-32 code.
 *
 */

#ifndef CRC32_H
#define	CRC32_H

/**
 * Calculate the CRC-32 code given a byte buffer.
 * 
 * @param buffer Buffer to get the crc-32 code
 * @param bufferSize Buffer size
 * 
 * @return Return the CRC-32 of the bytes
 */
unsigned int crc32(const char* buffer, int bufferSize);

#endif	/* CRC32_H */