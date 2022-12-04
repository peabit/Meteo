#pragma once
#include <Arduino.h>

enum ReturnStatus
{
    Success = 0,
    CheckSumError = -1,
    Timeout = -2,
    NoReply = -3
};

struct Meteo
{
    float temperature;
    int humidity;
    ReturnStatus returnStatus;
};

class DHT11
{
public:
    explicit DHT11(int pinNumber);
    Meteo get() const;

private:
    void tryConnectToSensor() const;
    bool isSensorConnected() const;
    unsigned long sendPulse(uint8_t pin, bool state, unsigned long timeout) const;
    bool checkControlSum(uint8_t responseBytes[]) const;
    uint8_t getHumidity(uint8_t responseBytes[]) const;
    float getTemperature(uint8_t responseBytes[]) const;

    const int _responseLengthInBytes = 5;
    int _pin;
};