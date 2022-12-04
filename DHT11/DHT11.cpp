#include <DHT11.h>

DHT11::DHT11(int pin)
{
    _pin = pin;
}

Meteo DHT11::get() const
{
    tryConnectToSensor();

    Meteo meteo;

    if (!isSensorConnected())
    {
        meteo.returnStatus = ReturnStatus::Timeout;
        return meteo;
    }

    uint8_t responseBytes[_responseLengthInBytes];

    for (int i = 0; i < _responseLengthInBytes; i++)
    {
        responseBytes[i] = 0;
    }

    // Cчитываем 40 бит данных
    // с одинаковым стартом — зажатием шины около 50 мкс и битом данных
    // датчик «отпускает» шину на ~27мкс если хочет передать «0», или на ~70мкс если хочет передать «1»

    int responseLengthInBits = 40;

    for (int i = 0; i < responseLengthInBits; i++)
    {
        sendPulse(_pin, LOW, 50);

        auto pulseLength = sendPulse(_pin, HIGH, 100);

        if (pulseLength > 0)
        {
            uint8_t responseByteIndex = i / 8;

            // Сдвинуть влево на 1 текущий байт ответа
            responseBytes[responseByteIndex] <<= 1;

            // Получить следующий бит ответа
            uint8_t responseBytesBit = pulseLength > 45 ? 1 : 0;

            // Добавить полученный бит к текущему байту ответа
            responseBytes[responseByteIndex] += responseBytesBit;
        }
        else
        {
            meteo.returnStatus = ReturnStatus::Timeout;
            return meteo;
        }
    }

    if (!checkControlSum(responseBytes))
    {
        meteo.returnStatus = ReturnStatus::CheckSumError;
        return meteo;
    }

    meteo.temperature = getTemperature(responseBytes);
    meteo.humidity = getHumidity(responseBytes);
    meteo.returnStatus = ReturnStatus::Success;

    return meteo;
}

unsigned long DHT11::sendPulse(uint8_t pin, bool state, unsigned long timeout) const
{
    unsigned long beginTime = micros();
    
    // Ожидание окончания текущего пульса
    while (digitalRead(pin) == state)
    {
        if (micros() - beginTime > timeout)
        {
            return 0;
        }
    }

    return micros() - beginTime;
}

void DHT11::tryConnectToSensor() const
{
    // Прижать шину к земле на 18 мс
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
    delay(18);

    // Отпустить шину
    pinMode(_pin, INPUT_PULLUP);
}

bool DHT11::isSensorConnected() const
{
    // В течении 20-40 мкс датчик зажимает шину в 0 и держит 80 мкс
    // потом отпускает на 80 мкс (формирует сигнал присутствия)
    if (sendPulse(_pin, HIGH, 40) == 0)
    {
        return false;
    }

    if (sendPulse(_pin, LOW, 80) == 0)
    {
        return false;
    }

    if (sendPulse(_pin, HIGH, 80) == 0)
    {
        return false;
    }

    return true;
}

bool DHT11::checkControlSum(uint8_t responseBytes[]) const
{
    if (responseBytes[4] != responseBytes[0] + responseBytes[1] + responseBytes[2] + responseBytes[3])
    {
        return false;
    }

    return true;
}

float DHT11::getTemperature(uint8_t responseBytes[]) const 
{
    float temperature = responseBytes[2] + (responseBytes[3] & 0x7F) * 0.1;

    // Температура считается отрицательной, если 1-ый бит 3-го байта равен 1 
    if (responseBytes[3] & 0x80)
    {
        temperature *= -1;
    }

    return temperature;
}

uint8_t DHT11::getHumidity(uint8_t responseBytes[]) const
{
    return responseBytes[0];
}