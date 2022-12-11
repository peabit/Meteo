#pragma once
#include <Arduino.h>

namespace dht11
{
    enum ReadStatus
    {
        Success = 0,
        CheckSumError = 1,
        Timeout = 2,
        NoReply = 3
    };

    struct Meteo
    {
        int temperature;
        int humidity;
    };

    class DHT11
    {
    public:
        explicit DHT11(int pinNumber);
        ReadStatus read();
        Meteo get() const;

    private:
        void tryConnectToSensor() const;
        bool isSensorConnected() const;
        unsigned long sendPulse(uint8_t pin, bool state, unsigned long timeout) const;
        bool checkControlSum(uint8_t responseBytes[]) const;
        int getHumidity(uint8_t responseBytes[]) const;
        int getTemperature(uint8_t responseBytes[]) const;

        int _pin;
        Meteo _meteo;
    };
}