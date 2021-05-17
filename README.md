# Thermocoupler interface library for multible sensors

## About the library
This tiny library is intended to be used with MAX6675 thermocouple interface chip. Libraty currently supports hardware SPI only. Library keeps polling time of the MAX6675 according to the datasheet.
This library is modified to able use multiple MAX6675 sensors.

## How to use
See included example, it's quite self-explanatory.
First create intanse of class:                                          Thermocoupler tcouple = Thermocoupler()
That asumes that you use hardware SPI.
if you want to use software SPI use:                                    Thermocoupler tcouple = Thermocoupler(CLKpin, DOpin)
Then use initialize SPI connection:                                     tcouple.begin()
Next you need to specify all chip select pins you are going to use.
This part of init is setting GPIO pins to OUTPUTs.                      tcouple.init(CSpin)
Do that for every pins you use.
To get temperature use:                                                 .readTempC(CSpin, type)
type parameter specifies driver chip type:                              1 = MAX6675, 2 = MAX31855


## Author
Marko Heikkilä
