// The MIT License (MIT)

// Copyright (c) 2013 lailongwei<lailongwei@126.com>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of 
// this software and associated documentation files (the "Software"), to deal in 
// the Software without restriction, including without limitation the rights to 
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of 
// the Software, and to permit persons to whom the Software is furnished to do so, 
// subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all 
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS 
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "llbc/common/Export.h"
#include "llbc/common/BeforeIncl.h"

#include "llbc/core/os/OS_Time.h"
#include "llbc/core/utils/Util_Text.h"

#include "llbc/core/time/TimeSpan.h"
#include "llbc/core/time/Time.h"

#if LLBC_TARGET_PLATFORM_WIN32
#pragma warning(disable:4996)
#endif

std::ostream &operator <<(std::ostream &stream, const LLBC_NS LLBC_Time &t)
{
    return stream<<t.ToString();
}

__LLBC_NS_BEGIN

const int LLBC_Time::NumOfSecondsPerDay = 86400;
const int LLBC_Time::NumOfMilliSecondsPerDay = 86400000;
#if LLBC_TARGET_PLATFORM_WIN32
LLBC_EXPORT const sint64 LLBC_Time::NumOfMicroSecondsPerDay = 86400000000I64;
LLBC_EXPORT const sint64 LLBC_Time::NumOfNanoSecondsPerDay = 86400000000000I64;
#else
LLBC_EXPORT const sint64 LLBC_Time::NumOfMicroSecondsPerDay = 86400000000LL;
LLBC_EXPORT const sint64 LLBC_Time::NumOfNanoSecondsPerDay = 86400000000000LL;
#endif

LLBC_EXPORT const int LLBC_Time::NumOfSecondsPerHour = 3600;
LLBC_EXPORT const int LLBC_Time::NumOfMilliSecondsPerHour = 3600000;
LLBC_EXPORT const sint64 LLBC_Time::NumOfMicroSecondsPerHour = 3600000000;
#if LLBC_TARGET_PLATFORM_WIN32
LLBC_EXPORT const sint64 LLBC_Time::NumOfNanoSecondsPerHour = 3600000000000I64;
#else
LLBC_EXPORT const sint64 LLBC_Time::NumOfNanoSecondsPerHour = 3600000000000LL;
#endif

LLBC_EXPORT const int LLBC_Time::NumOfSecondsPerMinute = 60;
LLBC_EXPORT const int LLBC_Time::NumOfMilliSecondsPerMinute = 60000;
LLBC_EXPORT const sint64 LLBC_Time::NumOfMicroSecondsPerMinute = 60000000;
#if LLBC_TARGET_PLATFORM_WIN32
LLBC_EXPORT const sint64 LLBC_Time::NumOfNanoSecondsPerMinute = 60000000000I64;
#else
LLBC_EXPORT const sint64 LLBC_Time::NumOfNanoSecondsPerMinute = 60000000000LL;
#endif

LLBC_EXPORT const int LLBC_Time::NumOfMilliSecondsPerSecond = 1000;
LLBC_EXPORT const sint64 LLBC_Time::NumOfMicroSecondsPerSecond = 1000000;
LLBC_EXPORT const sint64 LLBC_Time::NumOfNanoSecondsPerSecond = 1000000000;

LLBC_EXPORT const sint64 LLBC_Time::NumOfMicroSecondsPerMilliSecond = 1000;
LLBC_EXPORT const sint64 LLBC_Time::NumOfNanoSecondsPerMilliSecond = 1000000;

LLBC_EXPORT const sint64 LLBC_Time::NumOfNanoSecondsPerMicroSecond = 1000;

LLBC_Time LLBC_Time::Now()
{
    return LLBC_Time(LLBC_GetMicroSeconds());
}

int LLBC_Time::GetMilliSecond() const
{
    sint64 nowLocalMilliSeconds = 
        _time / NumOfMicroSecondsPerMilliSecond - LLBC_GetTimezone() * NumOfMilliSecondsPerSecond;
    return nowLocalMilliSeconds % NumOfMilliSecondsPerSecond;
}

int LLBC_Time::GetMicroSecond() const
{
    sint64 nowLocalMicroSeconds =
        _time - static_cast<sint64>(LLBC_GetTimezone()) * NumOfMicroSecondsPerSecond;
    return static_cast<int>(nowLocalMicroSeconds % NumOfMicroSecondsPerMilliSecond);
}

LLBC_Time LLBC_Time::GetDate() const
{
    sint64 timeZone = static_cast<sint64>(LLBC_GetTimezone() * NumOfMicroSecondsPerSecond);

    sint64 localTime = _time - timeZone;
    sint64 datePart = localTime / NumOfMicroSecondsPerDay * NumOfMicroSecondsPerDay;

    datePart += timeZone;

    return LLBC_Time(datePart);
}

LLBC_TimeSpan LLBC_Time::GetTimeOfDay() const
{
    sint64 timeZone = LLBC_GetTimezone() * NumOfMicroSecondsPerSecond;

    sint64 localTime = _time - timeZone;
    return localTime % NumOfMicroSecondsPerDay;
}

LLBC_String LLBC_Time::Format(const char *format) const
{
    char buf[32];
    memset(buf, 0, sizeof(buf));

    if (format)
        strftime(buf, sizeof(buf), format, &_localTimeStruct);
    else
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &_localTimeStruct);

    return buf;
}

LLBC_String LLBC_Time::FormatAsGmt(const char *format) const
{
    char buf[32];
    memset(buf, 0, sizeof(buf));

    if (format)
        strftime(buf, sizeof(buf), format, &_gmtTimeStruct);
    else
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &_gmtTimeStruct);

    return buf;
}

LLBC_Time LLBC_Time::FromTimeRepr(LLBC_String timeRepr)
{
    if (UNLIKELY(timeRepr.empty()))
        return LLBC_Time();

    // Split date, time
    LLBC_Strings dateTimes = timeRepr.split(' ', 1);
    if (dateTimes.size() == 1) // Only has date part or time part(try guess).
    {
        if (dateTimes[0].find('-') != LLBC_String::npos) // Is date part, append default time part.
            dateTimes.push_back("0:0:0.000");
        else // Is time part, insert default date part.
            dateTimes.insert(dateTimes.begin(), "1970-1-1");
    }

    const LLBC_String &datePart = dateTimes[0];
    const LLBC_String &timePart = dateTimes[1];

    // Split year,month,day
    LLBC_Strings dateParts = datePart.split('-', 2);
    if (dateParts.size() == 1) // Only has day part.
    {
        dateParts.insert(dateParts.begin(), "1");
        dateParts.insert(dateParts.begin(), "1970");
    }
    else if (dateParts.size() == 2) // Only has day and month parts.
    {
        dateParts.insert(dateParts.begin(), "1970");
    }

    // Split hour,minute,second
    LLBC_Strings timeParts = timePart.split(':', 2);
    if (timeParts.size() == 1) // Only has second part.
    {
        timeParts.insert(timeParts.begin(), "0");
        timeParts.insert(timeParts.begin(), "0");
    }
    else if (timeParts.size() == 2) // Only has second and minute parts.
    {
        timeParts.insert(timeParts.begin(), "0");
    }

    // Split time, microseconds 
    LLBC_Strings secondParts = timeParts[2].split('.', 1);
    if (secondParts.size() == 1) // Only has second part.
        secondParts.push_back("0");

    // Convert it
    int year = LLBC_Str2Int32(dateParts[0].c_str());
    int month = LLBC_Str2Int32(dateParts[1].c_str());
    int day = LLBC_Str2Int32(dateParts[2].c_str());

    int hour = LLBC_Str2Int32(timeParts[0].c_str());
    int minute = LLBC_Str2Int32(timeParts[1].c_str());
    int second = LLBC_Str2Int32(timeParts[2].c_str());
    int microSecond = LLBC_Str2Int32(secondParts[1].c_str());

    return FromTimeParts(year,
                         month,
                         day,
                         hour,
                         minute,
                         second,
                         static_cast<int>(microSecond / NumOfMicroSecondsPerMilliSecond),
                         static_cast<int>(microSecond % NumOfMicroSecondsPerMilliSecond));
}

LLBC_Time LLBC_Time::FromTimeStruct(const tm &timeStruct, int milliSecond, int microSecond)
{
    time_t clanderTimeInSecs = ::mktime(const_cast<tm *>(&timeStruct));
    return LLBC_Time(static_cast<sint64>(clanderTimeInSecs) * NumOfMicroSecondsPerSecond +
    milliSecond * NumOfMicroSecondsPerMilliSecond + microSecond);
}

LLBC_Time LLBC_Time::FromTimeParts(int year, int month, int day, int hour, int minute, int second, int milliSecond, int microSecond)
{
    tm timeStruct;
    timeStruct.tm_year = year - 1900;
    timeStruct.tm_mon = month - 1;
    timeStruct.tm_mday = day;

    if (year == 1970 && month == 1 && day == 1)
    {
        int tz = LLBC_GetTimezone();
        int totalSeconds = hour * NumOfSecondsPerHour +
            minute * NumOfSecondsPerMinute + second;
        if (tz < 0 && totalSeconds < -tz)
        {
            hour = -tz / NumOfSecondsPerHour;
            minute = (-tz % NumOfSecondsPerHour) / NumOfSecondsPerMinute;
            second = -tz % NumOfSecondsPerMinute;
        }
    }

    timeStruct.tm_hour = hour;
    timeStruct.tm_min = minute;
    timeStruct.tm_sec = second;


    return FromTimeStruct(timeStruct, milliSecond, microSecond);
}

LLBC_Time LLBC_Time::AddYears(int years) const
{
    if (years == 0)
        return *this;

    tm newTimeStruct;
    GetLocalTime(newTimeStruct);

    newTimeStruct.tm_year += years;
    bool isLeap = IsLeapYear(GetYear());
    if (isLeap && 
        GetMonth() == 2 && GetDay() == 29)
    {
        if (!IsLeapYear(GetYear() + years))
            newTimeStruct.tm_mday -= 1;
    }

    return FromTimeStruct(newTimeStruct, GetMilliSecond(), GetMicroSecond());
}

LLBC_Time LLBC_Time::AddMonths(int months) const
{
    LLBC_Time yearAddedTime = AddYears(months / 12);

    months %= 12;
    tm newTimeStruct;
    yearAddedTime.GetLocalTime(newTimeStruct);

    if (months >= 0)
    {
        int remainingMonths = 11 - newTimeStruct.tm_mon;
        if (months > remainingMonths)
        {
            newTimeStruct.tm_year += 1;
            newTimeStruct.tm_mon = months - (12 - newTimeStruct.tm_mon);
        }
        else
        {
            newTimeStruct.tm_mon += months;
        }
    }
    else
    {
        months = -months;
        int elapsedMonths = newTimeStruct.tm_mon + 1;
        if (months >= elapsedMonths)
        {
            newTimeStruct.tm_year -= 1;
            newTimeStruct.tm_mon = 12 - (months - elapsedMonths) - 1;
        }
        else
        {
            newTimeStruct.tm_mon -= months;
        }
    }

    newTimeStruct.tm_mday = MIN(newTimeStruct.tm_mday, 
        GetMonthMaxDays(yearAddedTime.GetYear(), newTimeStruct.tm_mon + 1));

    return FromTimeStruct(newTimeStruct, GetMilliSecond(), GetMicroSecond());
}

LLBC_Time LLBC_Time::AddDays(int days) const
{
    return *this + LLBC_TimeSpan(days * NumOfMicroSecondsPerDay);
}

LLBC_Time LLBC_Time::AddHours(int hours) const
{
    return *this + LLBC_TimeSpan(hours * NumOfMicroSecondsPerHour);
}

LLBC_Time LLBC_Time::AddMinutes(int minutes) const
{
    return *this + LLBC_TimeSpan(minutes * NumOfMicroSecondsPerMinute);
}

LLBC_Time LLBC_Time::AddSeconds(int seconds) const
{
    return *this + LLBC_TimeSpan(seconds * NumOfMicroSecondsPerSecond);
}

LLBC_Time LLBC_Time::AddMilliSeconds(int milliSeconds) const
{
    return *this + LLBC_TimeSpan(milliSeconds * NumOfMicroSecondsPerMilliSecond);
}

LLBC_Time LLBC_Time::AddMicroSeconds(int microSeconds) const
{
    return *this + LLBC_TimeSpan(static_cast<sint64>(microSeconds));
}

bool LLBC_Time::IsLeapYear(int year)
{
    return LLBC_IsLeapYear(year);
}

int LLBC_Time::GetMonthMaxDays(int year, int month)
{
    return LLBC_GetMonthMaxDays(year, month);
}

LLBC_TimeSpan LLBC_Time::GetIntervalTo(const LLBC_TimeSpan &span) const
{
    // Get past time(local time zone).
    sint64 localTime = _time - LLBC_GetTimezone() * NumOfMicroSecondsPerSecond;
    sint64 todayElapsed = localTime % NumOfMicroSecondsPerDay;

    // Calculate span value.
    sint64 spanVal = span.GetTotalMicroSeconds() - todayElapsed;
    if (spanVal < 0)
        spanVal = NumOfMicroSecondsPerDay + spanVal;

    return LLBC_TimeSpan(spanVal);
}

LLBC_TimeSpan LLBC_Time::GetIntervalTo(int hour, int minute, int second, int milliSecond, int microSecond) const
{
    return GetIntervalTo(LLBC_TimeSpan(0, hour, minute, second, milliSecond, microSecond));
}

LLBC_TimeSpan LLBC_Time::GetIntervalTo(const LLBC_Time &from, const LLBC_TimeSpan &span)
{
    return from.GetIntervalTo(span);
}

LLBC_TimeSpan LLBC_Time::GetIntervalTo(const LLBC_Time &from, int hour, int minute, int second, int milliSecond, int microSecond)
{
    return from.GetIntervalTo(hour, minute, second, milliSecond, microSecond);
}

LLBC_TimeSpan LLBC_Time::operator -(const LLBC_Time &time) const
{
    return LLBC_TimeSpan(_time - time._time);
}

LLBC_TimeSpan LLBC_Time::operator +(const LLBC_Time &time) const
{
    return LLBC_TimeSpan(_time - time._time);
}

LLBC_Time LLBC_Time::operator +(const LLBC_TimeSpan &span) const
{
    return LLBC_Time(_time + span.GetTotalMicroSeconds());
}

LLBC_Time LLBC_Time::operator -(const LLBC_TimeSpan &span) const
{
    return LLBC_Time(_time - span.GetTotalMicroSeconds());
}

LLBC_Time &LLBC_Time::operator =(const LLBC_Time &time)
{
    if (this == &time)
        return *this;
    else if (*this == time)
        return *this;

    _time = time._time;
    memcpy(&_localTimeStruct, &time._localTimeStruct, sizeof(tm));
    memcpy(&_gmtTimeStruct, &time._gmtTimeStruct, sizeof(tm));

    return *this;
}

LLBC_String LLBC_Time::ToString() const
{
    LLBC_String repr;
    return repr.format("%s.%06lld", Format().c_str(), GetMilliSecond() * NumOfMicroSecondsPerMilliSecond + GetMicroSecond());
}

bool LLBC_Time::DeSerialize(LLBC_Stream &stream)
{
    sint64 timeVal = 0;
    if (!stream.Read(timeVal))
        return false;

    _time = timeVal;
    UpdateTimeStructs();

    return true;
}

bool LLBC_Time::DeSerializeEx(LLBC_Stream &stream)
{
    sint64 timeVal = 0;
    if (!stream.ReadEx(timeVal))
        return false;

    _time = timeVal;
    UpdateTimeStructs();

    return true;
}

void LLBC_Time::UpdateTimeStructs()
{
    time_t calendarTime = static_cast<time_t>(_time / NumOfMicroSecondsPerSecond);
    #if LLBC_TARGET_PLATFORM_WIN32
    ::localtime_s(&_localTimeStruct, &calendarTime);
    ::gmtime_s(&_gmtTimeStruct, &calendarTime);
    #else
    ::localtime_r(&calendarTime, &_localTimeStruct);
    ::gmtime_r(&calendarTime, &_gmtTimeStruct);
    #endif
}

__LLBC_NS_END

#if LLBC_TARGET_PLATFORM_WIN32
#pragma warning(default:4996)
#endif

#include "llbc/common/AfterIncl.h"
