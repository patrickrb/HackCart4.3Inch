#ifndef TIME_MODULE_HPP
#define TIME_MODULE_HPP

#include <TinyGPS++.h>

class TimeModule
{
public:
    TimeModule(TinyGPSPlus &gpsInstance);
    const char *getTimeString();
    void setTimeZoneOffset(int offset);

private:
    TinyGPSPlus &gps;
    int timeZoneOffset;  // offset in hours
    char timeBuffer[12]; // "hh:mm:ss AM" format

    int adjustTimeZone(int hour, int offset);
};

#endif // TIME_MODULE_HPP
