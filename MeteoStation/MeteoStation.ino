#include <SimpleSerial.h>
#include <DHT11.h>

enum ResponseStatus 
{
  Success,
  InvalidCommand,
  SensorError  
};

const String command = "get";

// DHT11 sensor on 1 pin
dht11::DHT11 meteoSensor(1);

void setup(){}

void loop() 
{
    auto command = SimpleSerial.readLine();

    if (command.length() == 0) 
    {
      return;
    }
    
    if (command != "get") 
    {
        SimpleSerial.writeLine(ResponseStatus::InvalidCommand);
        return;
    }

    auto meteo = meteoSensor.get();

    if (meteoSensor.read() == dht11::ReadStatus::Success) 
    {
        auto meteo = meteoSensor.get();
        
        SimpleSerial.writeLine(
          String(ResponseStatus::Success) + ',' + 
          String(meteo.temperature)       + ',' + 
          String(meteo.humidity)
        );
    }
    else 
    {
        SimpleSerial.writeLine(ResponseStatus::SensorError);
    }
}
