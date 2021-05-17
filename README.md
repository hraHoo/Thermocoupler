# Thermocoupler interface library for multible sensors

## About the library
This tiny library is intended to be used with MAX6675 and MAX31855 thermocoupler interface chip. Library currently supports hardware SPI and software SPI.
This library is make especially to use multiple thermocoupler sensors. Of course you can use it if you have just one sensor.

## How to use
See included example, it's quite self-explanatory.
First create intanse of class:                                          Thermocoupler tcouple = Thermocoupler()
Above assumes that you use hardware SPI.
If you want to use software SPI use:                                    Thermocoupler tcouple = Thermocoupler(CLKpin, DOpin)
Then you have to initialize SPI connection:                             tcouple.begin()
Next you need to specify all chip select pins you are going to use.
This init is setting GPIO pins to OUTPUTs.                              tcouple.init(CSpin)
Do that for every pins you use.
To get temperature use:                                                 tcouple.readTempC(CSpin, type)
Return type is FLOAT.
type parameter specifies driver chip type:                              1 = MAX6675, 2 = MAX31855


## Author
Marko Heikkilä
