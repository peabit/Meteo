#include <DHT11.h>

const String command = "get\n";
const String invalidCommandResponse = "error,Invalid command";

// DHT11 sensor on 1 pin
DHT11 meteoSensor(1);

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  if (Serial.available() == 0) 
  {
    return;
  }

  if (Serial.available() != command.length()) 
  {
    while(Serial.available() > 0) 
    {
      Serial.read();
    }

    Serial.println(invalidCommandResponse);
    return;
  }

  String inputCommand = "";
  
  while(Serial.available() > 0)
  {
    inputCommand += (char)Serial.read();
  }

  if (inputCommand == command) 
  {
    auto meteo = meteoSensor.get();

    if (meteo.returnStatus == ReturnStatus::Success)
    {
      auto successResponse =
        "success," + String(meteo.temperature) + ',' + String(meteo.humidity);
        
      Serial.println(successResponse);  
    }
    else {
      Serial.println("Error;Sensor error");
    }
  }
  else
  {
    Serial.println(invalidCommandResponse);
  }
}
