#include <SimpleSerial.h>

namespace simpleSerial
{
    SimpleSerial::SimpleSerial(int speed)
    {
        Serial.begin(speed);
    }

    String SimpleSerial::readLine()
    {
        String result;

        if (Serial.available() == 0)
        {
            return result;
        }

        while (Serial.available() > 0)
        {
            result += (char)Serial.read();
        }

        return result.substring(0, result.indexOf('\n'));
    }

    void SimpleSerial::writeLine(String line)
    {
        Serial.println(line);
    }

    void SimpleSerial::writeLine(int value)
    {
        writeLine(String(value));
    }

    class SimpleSerial SimpleSerial(9600);
}