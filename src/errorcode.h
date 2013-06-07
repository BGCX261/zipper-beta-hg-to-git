/* 
 * File:   errorcode.h
 * Author: Daniela Meneses
 * Description: Contains the error code that the library will manage as a status response after to 
 * perform a task.
 *
 * Created on May 13, 2013, 4:45 PM
 */

#ifndef ZIPPERERRORCODE_H
#define	ZIPPERERRORCODE_H

/**
 * Error code enum that defines the library standard return value when some feature 
 * from the zipper library is used.
 */
enum ErrorCode
{
    OK = 0,
    FILE_NOT_FOUND = 1,
    UNSUPPORTED_COMPRESSION = 2,
    CORRUPTED_FILE = 3,
    INVALID_PARAMETERS = 4,
    CAN_NOT_OPEN_INPUT_FILE = 5,
    CAN_NOT_FIND_TARGET_PATH = 6
};

#endif	/* ZIPPERERRORCODE_H */
