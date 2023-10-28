#pragma once

#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

class Compass
{
public:
    Compass(int id = 12345);
    void init();
    void displaySensorDetails();
    void update();

private:
    Adafruit_HMC5883_Unified mag;
};
