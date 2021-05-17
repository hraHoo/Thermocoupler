//
//    FILE: Thermocoupler.cpp
//  AUTHOR: Marko Heikkilä
// VERSION: 0.1.2
// PURPOSE: Arduino library for MAX6675 chip for K type thermocouple
//    DATE: 2021-11-05
//     URL: https://github.com/hraHoo
//
//  HISTORY:
//  0.1.0  2021-11-05  first version MAX6675 read temperature using soft SPI
//  0.1.2  2021-11-05  - Hardware SPI added
//                     - Method version added
//  0.1.3  12-05-2021  - rawdata read is separated, now _rawdata16 and _rawdata32 (just void no return, private variable)
//	0.2.0  17-05-2021  - MAX31855 impementation, sw and hw SPI
//
//
//
//
//
//	TODO:	- some kind of status or error indication
//
//

#ifndef THERMOCOUPLER_h
#define THERMOCOUPLER_h


#include "Arduino.h"
#include "SPI.h"

// global defenitions
#define THERMOCOUPLER_VERSION        	"0.2.1"
#define THERMOCOUPLER_NO_TEMPERATURE	-999
#define CONVERSION_RATIO				0.25
#define SPI_Settings (SPISettings(4000000, MSBFIRST, SPI_MODE2))


// defenitions for MAX6675
#define MAX6675_THERMOCOUPLER_OPEN_BIT	0x04
#define MAX6675_THERMOCOUPLER_OPEN 		-1.0

// defenitions for MAX31855

// value of _rawData32
// BITS     DESCRIPTION
// ----------------------
// 00 - 02  STATUS
//      03  RESERVED
// 04 - 15  INTERNAL
//      16  FAULT-BIT
//      17  RESERVED
// 18 - 30  TEMPERATURE (RAW)
//      31  SIGN

class Thermocoupler
{
	private:
		float _temp6675();
		float _temp31855();
		void _swspiread16(void);
		void _swspiread32(void);
		void _hwspiread16(void);
		void _hwspiread32(void);
		float _currentTemp;
		float _internal;
		uint16_t _rawData16;
		uint32_t _rawData32;
		uint8_t _cs;						// current temperature reading sensor CS
		uint8_t  _sclk;
		uint8_t  _miso;
		int _hwSPI = -1;
			
	public:
		Thermocoupler();
		Thermocoupler(uint8_t SCLK, uint8_t MISO);
		String Version();
		void begin();
		void init(uint8_t SSPin);
		float readTempC(uint8_t SSPin, uint8_t Type);
		float convertToFahrenheith(float temp);
};



#endif