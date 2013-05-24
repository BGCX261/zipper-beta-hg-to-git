#include <stdio.h>
#include "zipperutils.h"

short parseDateToMSDosFormat(tm* date)
{
    if(!date)
    {
        return 0;
    }
    
    char buffer[11];
    int year;
    int month;
    int day;
    
    strftime(buffer, 11, "%Y:%m:%d", date);
    sscanf(buffer, "%d:%d:%d", &year, &month, &day);
    
    if(year != 0)
    {
        year -= 1980; //Following the MS-Dos date standard format
    }
    
    return (short) (year << 9) | (month << 5) | day; // Store the year month and day
}

short parseTimeToMSDosFormat(tm* time)
{
    if(!time)
    {
        return 0;
    }
    
    char buffer[11];
    int hour;
    int minute;
    int second;
    
    strftime(buffer, 11, "%H:%M:%S", time);
    sscanf(buffer, "%d:%d:%d", &hour, &minute, &second);
    
    if (second != 0)
    {
        second /= 2; //Following the MS-Dos date standard format
    }
    
    return (short) (hour << 11) | (minute << 5) | second; // Store the hour minute and second
}
