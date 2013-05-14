/* 
 * File:   errorcode.h
 * Author: Daniela Meneses
 *
 * Created on May 13, 2013, 4:45 PM
 */

#ifndef ZIPPERERRORCODE_H
#define	ZIPPERERRORCODE_H

/**
 * Error code enum that defines the library standard return value when some feature 
 * from the zipper library is used.
 */
enum ErrorCode {
    OK = 0,
    FILE_NOT_FOUND = 1,
    UNSUPPORTED_COMPRESSION = 2,
    CORRUPTED_FILE = 3
};

#endif	/* ZIPPERERRORCODE_H */
