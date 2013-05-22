#include <stdio.h>
#include "zipperutils.h"

short parseDateToMSDosFormat(tm* date)
{
    if(!date)
    {
        return 0;
    }
    
    char buffer[11];
    strftime(buffer, 11, "%Y:%m:%d", date);
    int year;
    int month;
    int day;
    
    sscanf(buffer, "%d:%d:%d", &year, &month, &day);
    
    if(year != 0)
    {
        year -= 1980;
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
    strftime(buffer, 11, "%H:%M:%S", time);
    int hour;
    int minute;
    int second;
    sscanf(buffer, "%d:%d:%d", &hour, &minute, &second);
    
    if (second != 0)
    {
        second /= 2;
    }
    
    return (short) (hour << 11) | (minute << 5) | second; // Store the hour minute and second
}
