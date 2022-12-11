#include <SimpleSerial.h>
#include <DHT11.h>

enum ResponseStatus 
{
  Success,
  InvalidCommand,
  SensorError  
};

// DHT11 sensor on 1 pin
dht11::DHT11 meteoSensor(1);

void setup(){}

void loop() 
{
    auto command = simpleSerial::SimpleSerial.readLine();

    if (command.length() == 0) 
    {
      return;
    }
    
    if (command != "get") 
    {
        simpleSerial::SimpleSerial.writeLine(ResponseStatus::InvalidCommand);
        return;
    }

    auto readStatus = meteoSensor.read();
    
    if (readStatus != dht11::ReadStatus::Success) 
    {
      simpleSerial::SimpleSerial.writeLine(ResponseStatus::SensorError);
      return;
    }
    
    auto meteo = meteoSensor.get();
        
    simpleSerial::SimpleSerial.writeLine(
      String(ResponseStatus::Success) + ',' + 
      String(meteo.temperature)       + ',' + 
      String(meteo.humidity)
    );
}