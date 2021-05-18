#include "Thermocoupler.h"
#define MAX_SENSOR_COUNT 15

const byte CS_6675_PINS[] = {0, 4};
float celsius[MAX_SENSOR_COUNT];


// meke instance of thermocouåpler class using default hardware SPI pins
Thermocoupler tcouple = Thermocoupler();

void printTemps()
{
  for (int i = 0; i < sizeof(CS_6675_PINS); i++)
  {
    Serial.print("Sensor 6675 temperature in pin ");
    Serial.print(CS_6675_PINS[i]);
    Serial.print(" = ");
    Serial.println(celsius[i]);
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
  for (int i = 0; i < sizeof(CS_6675_PINS); i++)
  {
    tcouple.init(CS_6675_PINS[i]);
  }
}

void loop()
{
  // get temperatures
  for (int i = 0; i < sizeof(CS_6675_PINS); i++)
  {
    celsius[i] = tcouple.readTempC(CS_6675_PINS[i], 1);
  }
 
  printTemps();
  delay(5000);
}