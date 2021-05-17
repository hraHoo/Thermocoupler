# Thermocoupler interface library for multible sensors
## Contents
1. About the library
2. How to use
3. Author

## 1. About the library
This tiny library is intended to be used with MAX6675 thermocouple interface chip. Libraty currently supports hardware SPI only. Library keeps polling time of the MAX6675 according to the datasheet.
This library is modified to able use multiple MAX6675 sensors.
## 2. How to use
See included example, it's quite self-explanatory.
In method .readreadTempC(CS) you just give sensors chip select pin in parameter.
## 3. Author
Original author Evgeny Kremer, evgeny.kremer@gmail.com
New version Marko Heikkilä
