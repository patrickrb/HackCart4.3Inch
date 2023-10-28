#include "time.hpp"

TimeModule::TimeModule(TinyGPSPlus &gpsInstance) : gps(gpsInstance), timeZoneOffset(-6) {}

const char *TimeModule::getTimeString()
{
    if (gps.time.isValid())
    {
        int hour = gps.time.hour();
        const char *ampm = "AM";

        hour = adjustTimeZone(hour, timeZoneOffset);

        if (hour >= 12)
        {
            ampm = "PM";
            if (hour > 12)
            {
                hour -= 12;
            }
        }
        if (hour == 0)
        {
            hour = 12;
        }

        sprintf(timeBuffer, "%02d:%02d:%02d %s", hour, gps.time.minute(), gps.time.second(), ampm);
        return timeBuffer;
    }
    return "Invalid time data";
}

int TimeModule::adjustTimeZone(int hour, int offset)
{
    hour += offset;
    if (hour < 0)
        hour += 24;
    if (hour >= 24)
        hour -= 24;
    return hour;
}

void TimeModule::setTimeZoneOffset(int offset)
{
    timeZoneOffset = offset;
}
