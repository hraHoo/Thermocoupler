//
//    FILE: Thermocoupler.cpp
//  AUTHOR: Marko Heikkilä
// VERSION: 0.2.3
// PURPOSE: Arduino library for MAX6675 chip for K type thermocouple
//    DATE: 2021-11-05
//     URL: https://github.com/hraHoo/Thermocoupler
//
//  HISTORY:
//  0.1.0  11-05-2021  - first version MAX6675 read temperature using soft SPI
//  0.1.2  12-05-2021  - Hardware SPI added
//                     - Method version added
//  0.1.3  12-05-2021  - rawdata read is separated, now _rawdata16 and _rawdata32 (just void no return, private variable)
//	0.2.0  17-05-2021  - MAX31855 impementation, sw and hw SPI
//	0.2.3  18-05-2021  - Bug and typo fix.
//
//
//
//
//  MAX6675  temperature measurement range is    0°C to +1024°C
//  MAX31855 temperature measurement range is -270°C to +1800°C. Accuracy of ±2°C in range -200°C to +700°C
//
//
//
//	TODO:	- some kind of status or error indication
//
//


#include <Thermocoupler.h>


Thermocoupler::Thermocoupler()
{
	_hwSPI       = 1;
  _rawData16     = 0;
  _rawData32     = 0;
}

Thermocoupler::Thermocoupler(const uint8_t sclk, const uint8_t miso)
{
  _hwSPI       = 0;
  _sclk        = sclk;
  _miso        = miso;
  _rawData16     = 0;
  _rawData32     = 0;
}

String Thermocoupler::Version(){
  return THERMOCOUPLER_VERSION;
}

//======================================================
//                        PUBLIC
//======================================================

/*
	init SPI (hardware or software)
*/
void Thermocoupler::begin()
{
  if (_hwSPI)
  {
    SPI.begin();
    SPI.beginTransaction(SPI_Settings);
    delay(50);
  }
  else
  {
    pinMode(_sclk, OUTPUT);
    //digitalWrite(_sclk, HIGH);
    pinMode(_miso, INPUT);
  }
}

/*
	init GPIO-pin to output and set it high.
	Call this ones for all CS pins in use
*/
void Thermocoupler::init(uint8_t CS)
{
	pinMode(CS, OUTPUT);
	digitalWrite(CS, HIGH);
}

/*
	read needs to know whits thermocoupler you wand to read, that's why CS parameter.
	Type we need to know how to read thermocoupler
*/
float Thermocoupler::readTempC(uint8_t CS, uint8_t Type)
{
  _cs = CS;
  // return temp if SPI conection is initialized (.begin())
  if (_hwSPI >= 0)
  {
    if (Type == 1)
    {
      float temp6675 = _temp6675();
      return temp6675;
    }
    else if (Type == 2)
    {
      float temp31855 = _temp31855();
      return temp31855;
    }
  }
  else{
    return THERMOCOUPLER_NO_TEMPERATURE;
  }
}

float Thermocoupler::convertToFahrenheith(float tempToConvert)
{
	return (( tempToConvert * 9.0 ) / 5.0) + 32;
}


//======================================================
//                        PRIVAT
//======================================================

float Thermocoupler::_temp6675()
{
  if (_hwSPI)
  {
		_hwspiread16();
	}
  else
  {
    _swspiread16();
  }

  if (_rawData16 & MAX6675_THERMOCOUPLER_OPEN_BIT)
  {
    return MAX6675_THERMOCOUPLER_OPEN;
  }
  _rawData16 >>= 3;
  _currentTemp = _rawData16 * CONVERSION_RATIO;
  digitalWrite(_cs, HIGH);
  return _currentTemp;  
}

float Thermocoupler::_temp31855()
{
  if (_hwSPI)
  {
		_hwspiread32();
	}
  else
  {
    _swspiread32();
  }
  _rawData32 >>= 3;

  // reserved bit 3, always 0
  _rawData32 >>= 1;

  // process internal bit 4-15
  _internal = (_rawData32 & 0x07FF) * 0.0625;
  // negative flag set ?
  if (_rawData32 & 0x0800) 
  {
    _internal = -128 + _internal;
  }
  _rawData32 >>= 12;

  // Fault bit ignored as we have the 3 status bits
  // _fault = value & 0x01;
  _rawData32 >>= 1;

  // reserved bit 17, always 0
  _rawData32 >>= 1;

  // process temperature bit 18-30 + sign bit = 31
  _currentTemp = (_rawData32 & 0x1FFF) * CONVERSION_RATIO;
  // negative flag set ?
  if (_rawData32 & 0x2000)
  {
    _currentTemp = -2048 + _currentTemp;
  }

  digitalWrite(_cs, HIGH);
  return _currentTemp;  
}

void Thermocoupler::_swspiread16(void) 
{
  int i;
  uint16_t data = 0;

  digitalWrite(_cs, LOW);
  delayMicroseconds(10);

  for (i = 15; i >= 0; i--) 
  {
    digitalWrite(_sclk, LOW);
    delayMicroseconds(10);
    if (digitalRead(_miso)) 
    {
      // set the bit to 0 no matter what
      data |= (1 << i);
    }

    digitalWrite(_sclk, HIGH);
    delayMicroseconds(10);
  }

  _rawData16 = data;
}

void Thermocoupler::_swspiread32(void) 
{
  int i;
  uint32_t data = 0;

  digitalWrite(_cs, LOW);
  delayMicroseconds(10);

  for (i = 31; i >= 0; i--) 
  {
    digitalWrite(_sclk, LOW);
    delayMicroseconds(10);
    if (digitalRead(_miso)) 
    {
      // set the bit to 0 no matter what
      data |= (1 << i);
    }

    digitalWrite(_sclk, HIGH);
    delayMicroseconds(10);
  }

  _rawData32 = data;
}
void Thermocoupler::_hwspiread16(void) 
{
    digitalWrite(_cs, LOW);
    delayMicroseconds(1);
		_rawData16 = SPI.transfer16(0x00);
		digitalWrite(_cs, HIGH);
		SPI.endTransaction();
}


  void Thermocoupler::_hwspiread32(void) 
{
    digitalWrite(_cs, LOW);
    delayMicroseconds(1);
		_rawData32 = SPI.transfer16(0x00);
    _rawData32 <<= 16;
    _rawData32 |= SPI.transfer16(0x00);
		digitalWrite(_cs, HIGH);
		SPI.endTransaction();
}