#include "Thermocoupler.h"
#define MAX_SENSOR_COUNT 15

const int CS_6675_PINS[] = {0, 4};
float celsius[MAX_SENSOR_COUNT];


// meke instance of thermocouåpler class using default hardware SPI pins
Thermocoupler tcouple = Thermocoupler();


// meke instance of thermocouåpler class using custom SPI pins (software SPI)
// define SPI pins
const byte thermoDO = 12;
const byte thermoCLK = 14;
//Thermocoupler tcouple = Thermocoupler(thermoCLK, thermoDO);

void printTemps()
{
  for (int i = 0; i < sizeof(CS_6675_PINS); i++)
  {
    Serial.print("Temperature 6675");
    Serial.print(" in pin ");
    Serial.print(CS_6675_PINS[i]);
    Serial.print(" = ");
    Serial.println(celsius[i]);
  }
}

void setup()
{
  Serial.begin(115200);
  delay(500);
  Serial.println("**** Thermocouple library ****");
  Serial.print("Versio: ");
  Serial.println(tcouple.Version());

  // initialize SPI connection
  tcouple.begin();

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
  for (int i = 0; i < CS31855Count; i++)

  printTemps();
  delay(5000);
}