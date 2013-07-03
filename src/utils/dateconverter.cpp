#include "dateconverter.h"
#include <stdio.h>

DateConverter::DateConverter()
{
    time_ = new tm();
}

DateConverter::DateConverter(tm* time)
{
    time_ = time;
}

DateConverter::DateConverter(DateConverter& dateConverter)
{
    dateConverter.time_ = time_;
}

DateConverter::~DateConverter()
{
    if (time_)
    {
        delete time_;
    }
}

short DateConverter::parseTimeToMSDosFormat()
{
    if(!time_)
    {
        return 0;
    }
    
    char buffer[11];
    int hour;
    int minute;
    int second;
    
    strftime(buffer, 11, "%H:%M:%S", time_);
    sscanf(buffer, "%d:%d:%d", &hour, &minute, &second);
    
    if (second != 0)
    {
        second /= 2; //Following the MS-Dos date standard format
    }
    
    return (short) (hour << 11) | (minute << 5) | second; // Store the hour minute and second
}

short DateConverter::parseDateToMSDosFormat()
{
    if(!time_)
    {
        return 0;
    }
    
    char buffer[11];
    int year;
    int month;
    int day;
    
    strftime(buffer, 11, "%Y:%m:%d", time_);
    sscanf(buffer, "%d:%d:%d", &year, &month, &day);
    
    if(year != 0)
    {
        year -= 1980; //Following the MS-Dos date standard format
    }
    
    return (short) (year << 9) | (month << 5) | day; // Store the year month and day
}

tm* DateConverter::parseMSDosToTm(const short date, const short time)
{
    tm* ans = new tm();
    
    int year = date >> 9 & ((1 << 7) - 1);
    int month = date >> 5 & 0xF;
    int day = date & ((1 << 5) - 1);
    
    int hour = time >> 11 & ((1 << 5) - 1);
    int minute = time  >> 5 & ((1 << 6) - 1);
    int second = time & ((1 << 5) - 1);
    
    ans->tm_year = year + 1980 - 1900;
    ans->tm_mon = month - 1;
    ans->tm_mday = day;
    
    ans->tm_hour = hour;
    ans->tm_min = minute;
    ans->tm_sec = second * 2;
    mktime(ans);
    
    return ans;
}
