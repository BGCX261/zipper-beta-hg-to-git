/* 
 * File:   dateconverter.h
 * Author: Luis Aguirre
 * Description: This file provide a converter that parse the date and time in MS-Dos 
 * format and inverse.
 *
 * Created on june 6, 2013, 06:49 PM
 */

#ifndef DATECONVERTER_H
#define	DATECONVERTER_H
#include <time.h>

/**
 * Parse date and time in MS-Dos format to save in zip files.
 */
class DateConverter
{
public:
    
    /**
     * Initialize the time in null.
     */
    DateConverter();
    
    /**
     * Constructor copy.
     * 
     * @param dateConverter
     */
    DateConverter(DateConverter& dateConverter);
    
    /**
    * Store the time information in two bytes following the MS-Dos standard time format.
    * MS-dos standard date format consist in save the hours minutes and seconds in two bytes
    * 
    * The format is the next:
    * 
    *      HHHHH The first five bits to the hours. Hours are always within 0-23 range.
    *      MMMMMM The next six bits to the minutes. Minutes are always within 0-59 range.
    *      SSSSS The last five bits to the seconds. Seconds are actually not 0-59 but rather 0-29 
     *     as there are only 32 possible values – to get actual seconds multiply this field by 2.
    * 
    * @return The time parsed
    */
    short parseTimeToMSDosFormat(tm* time);
    
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
    * @return The date parsed
    */
    short parseDateToMSDosFormat(tm* time);
    
    /**
     * Parse the time and date in MS-Dos format to a tm structure.
     * 
     * @param date MS-Dos Date
     * @param timeMS-Dos time
     * @param datetime The tm structure that will save the parsed date and time.
     */
    void parseMSDosToTm(const short date, const short time, tm* datetime);
};

#endif	/* DATECONVERTER_H */
