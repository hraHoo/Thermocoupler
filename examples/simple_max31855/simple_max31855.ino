#include "Thermocoupler.h"

#define MAX_SENSOR_COUNT 15

const byte CS_31855_PINS[] = {2};
float celsius[MAX_SENSOR_COUNT];


// meke instance of thermocouåpler class using default hardware SPI pins
Thermocoupler tcouple = Thermocoupler();

void printTemps()
{
  for (int i = 0; i < sizeof(CS_31855_PINS); i++)
  {  
    Serial.print("Sensor 31855 temperature in pin ");
    Serial.print(CS_31855_PINS[i]);
    Serial.print(" = ");
    Serial.println(celsius[i], 2);
  }
  Serial.println("----------------------");
}

void setup()
{
  Serial.begin(115200);
  delay(500);
  Serial.println("**** Thermocouple library ****");
  Serial.print("Versio: ");
  Serial.println(tcouple.Version());

  // initialize SPI connection
  // hardware SPI
  tcouple.begin();

  // define custom software SPI pins
  const byte thermoDO = 12;
  const byte thermoCLK = 14;
  //tcouple.begin(thermoCLK, thermoDO);  


  // initialize all sensor select GPIO-pins to output
  for (int i = 0; i < sizeof(CS_31855_PINS); i++)
  {  
    tcouple.init(CS_31855_PINS[i]);
  }
}

void loop()
{
  // get temperatures
  for (int i = 0; i < sizeof(CS_31855_PINS); i++)
  {  
    celsius[i] = tcouple.readTempC(CS_31855_PINS[i], 2);
  }

  printTemps();
  delay(5000);
}