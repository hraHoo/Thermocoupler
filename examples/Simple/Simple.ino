#include "Thermocoupler.h"

#define DEBUG_THERMO

#define MAX_SENSOR_COUNT 15

const int CS_6675_PINS[] = {0, 4};
int CS6675Count;
const int CS_31855_PINS[] = {2};
int CS31855Count;
float celsius[MAX_SENSOR_COUNT];


// meke instance of thermocouåpler class using default hardware SPI pins
Thermocoupler tcouple = Thermocoupler();


// make instance of thermocouåpler class using custom SPI pins (software SPI)
// define SPI pins
const byte thermoDO = 12;
const byte thermoCLK = 14;
//Thermocoupler tcouple = Thermocoupler(thermoCLK, thermoDO);

void printTemps()
{
  for (int i = 0; i < CS6675Count; i++)
  {
    Serial.print("Temperature 6675");
    Serial.print(" in pin ");
    Serial.print(CS_6675_PINS[i]);
    Serial.print(" = ");
    Serial.println(celsius[i]);
  }
  for (int i = 0; i < CS31855Count; i++)
  {  
    Serial.print("Temperature 31855");
    Serial.print(" in pin ");
    Serial.print(CS_31855_PINS[i]);
    Serial.print(" = ");
    Serial.println(celsius[CS6675Count + i], 2);
    Serial.println("----------------------");
  }
}

void setup()
{
  Serial.begin(115200);
  delay(500);
  Serial.println("**** Thermocouple library ****");
  Serial.print("Versio: ");
  Serial.println(tcouple.Version());

  CS6675Count = sizeof(CS_6675_PINS) / sizeof(int);
  CS31855Count = sizeof(CS_31855_PINS) / sizeof(int);

  if (CS6675Count + CS31855Count > MAX_SENSOR_COUNT)
  {
    Serial.println("Too many sensor pin defenition. Max is 15");
    while(true)
    {
      delay(1);
    }
  }
  else
  {
    Serial.print("You have ");
    Serial.print(CS6675Count);
    Serial.print(" Max6675 sensor defined and ");
    Serial.print(CS31855Count);
    Serial.println(" Max31855 sensor defined\n\n");
  }
  
  // initialize SPI connection
  tcouple.begin();

  // initialize all sensor select GPIO-pins to output
  for (int i = 0; i < CS6675Count; i++)
  {
    tcouple.init(CS_6675_PINS[i]);
  }
  for (int i = 0; i < CS31855Count; i++)
  {  
    tcouple.init(CS_31855_PINS[i]);
  }
}

void loop()
{
  // get temperatures
  for (int i = 0; i < CS6675Count; i++)
  {
    celsius[i] = tcouple.readTempC(CS_6675_PINS[i], 1);
  }
  for (int i = 0; i < CS31855Count; i++)
  {  
    celsius[CS6675Count + i] = tcouple.readTempC(CS_31855_PINS[i], 2);
  }

  printTemps();
  delay(5000);
}