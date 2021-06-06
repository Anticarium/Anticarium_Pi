#pragma once
#include <wiringPi.h>
#include <cinttypes>

#define DHTLIB_OK				0
#define DHTLIB_ERROR_CHECKSUM	-1
#define DHTLIB_ERROR_TIMEOUT	-2

class Dht11
{
public:
    int read(int pin);
    int getHumidity();
    int getTemperature();
private:
    int humidity;
	int temperature;
};
