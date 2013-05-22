/* 
 * File:   zipperutils.h
 * Author: Luis Aguirre
 * Description: Has utils functions to build the zip structure.
 *
 * Created on 20 de mayo de 2013, 03:27 PM
 */

#ifndef ZIPPERUTILS_H
#define	ZIPPERUTILS_H

#include <iostream>

/**
 * Store the date information in two bytes following the MS-Dos standard date format.
 * 
 * @param date To parse
 * 
 * @return The date parsed
 */
short parseDateToMSDosFormat(tm* date);

/**
 * Store the time information in two bytes following the MS-Dos standard time format.
 * 
 * @param time To parse
 * 
 * @return The time parsed
 */
short parseTimeToMSDosFormat(tm* time);

#endif	/* ZIPPERUTILS_H */

