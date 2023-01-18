/*! \file OPT3002.h
    \brief Library for managing the OPT3002 sensor from TI.

    This work is licensed under the Creative Commons Attribution 4.0 
	International License. To view a copy of this license, 
	visit http://creativecommons.org/licenses/by/4.0/ or send 
	a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
	
    Version : 1.0
	Author  : Alba0404
*/

/*! \def OPT3002_h
	\brief The library flag
*/
#ifndef OPT3002_h
#define OPT3002_h

// Includes
#include <inttypes.h>


// Defines
#define OPT3002_REGISTER_RESULT		0x00
#define OPT3002_REGISTER_CONFIG		0x01
#define OPT3002_REGISTER_LIMIT_LOW	0x02
#define OPT3002_REGISTER_LIMIT_HIGH	0x03
#define OPT3002_REGISTER_ID			0x7E

#define OPT3002_I2C_ADDR_GND		0x44
#define OPT3002_I2C_ADDR_VDD		0x45
#define OPT3002_I2C_ADDR_SDA		0x46
#define OPT3002_I2C_ADDR_SCL		0x47


// Class
class OPT3002
{
	private:
		uint8_t _address;
		uint16_t _readRegister(uint8_t addr);
	
	public:
		OPT3002();
		int8_t ON(uint8_t address);
		uint16_t readManufacturerID();
		uint16_t readConfiguration();
		float readResult();
		float readLowLimit();
		float readHighLimit();
};

#endif
