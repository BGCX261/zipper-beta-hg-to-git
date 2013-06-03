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
#include <list>
#include "../compressor/fileheader.h"
#include "filenotfoundexception.h"
#include "../exceptions/notzipfileexception.h"

/**
 * Store the date information in two bytes following the MS-Dos standard date format.
 * The MS-Dos standard Date format consist in save the Year, Month and Day in two bytes
 * 
 * The format is the next:
 * 
 *      YYYYYYY The first seven bits to the years. Starts from 1980 and continues for 127 years.
 *      MMMM The next four bits to the month. The month is always within 1-12 range.
 *      DDDDD The last five bits to the day of month. Day of month is always within 1-31 range.
 * 
 * @param date To parse
 * 
 * @return The date parsed
 */
short parseDateToMSDosFormat(tm* date);

/**
 * Store the time information in two bytes following the MS-Dos standard time format.
 * MS-dos standard date format consist in save the hours minutes and seconds in two bytes
 * 
 * The format is the next:
 * 
 *      HHHHH The first five bits to the hours. Hours are always within 0-23 range.
 *      MMMMMM The next six bits to the minutes. Minutes are always within 0-59 range.
 *      SSSSS The last five bits to the seconds. Seconds are actually not 0-59 but rather 0-29 as there 
 *            are only 32 possible values – to get actual seconds multiply this field by 2.
 * 
 * @param time To parse
 * 
 * @return The time parsed
 */
short parseTimeToMSDosFormat(tm* time);

std::list<FileHeader*>& navigate(const char* path) throw (FileException);

#endif	/* ZIPPERUTILS_H */

