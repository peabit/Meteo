#pragma once
#include <Arduino.h>

namespace simpleSerial
{
class SimpleSerial
{
public:
    SimpleSerial(int speed);
    String readLine();
    void writeLine(String line);
    void writeLine(int value);
};

extern SimpleSerial SimpleSerial;
}