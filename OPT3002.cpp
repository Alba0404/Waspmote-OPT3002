/*! \file OPT3002.c
    \brief Library for managing the OPT3002 sensor from TI.

    This work is licensed under the Creative Commons Attribution 4.0 
	International License. To view a copy of this license, 
	visit http://creativecommons.org/licenses/by/4.0/ or send 
	a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
	
    Version : 1.0
	Author  : Alba0404
*/

#ifndef __WPROGRAM_H__
  #include "WaspClasses.h"
#endif

#include <OPT3002.h>


// ============================================================
// Empty constructor.
OPT3002::OPT3002()
{
}

// ============================================================
/*!
 * \brief Start the sensor and define its address on the I2C bus.
 * \param uint8_t address : The address of the sensor :
 *                - OPT3002_I2C_ADDR_GND (default)
 *                - OPT3002_I2C_ADDR_VDD
 *                - OPT3002_I2C_ADDR_SDA
 *                - OPT3002_I2C_ADDR_SCL
 * \return int8_t code : 0 if ok, -1 otherwise.
 */
int8_t OPT3002::ON(uint8_t address)
{
	_address = address;
    I2C.begin();
    delay(100);
	uint8_t buffer[2] = {0xC4, 0x10};
	uint8_t *data = buffer;
	
	I2C.write((uint8_t)_address, 
	          (uint8_t)OPT3002_REGISTER_CONFIG,
			  data, 
			  (uint16_t)2);
		  
    
    if(readManufacturerID() == 0x5449)
    {
        return 0;
    }
    return -1;
}

// ============================================================
/*!
 * \brief Return the manufacturer ID. By default it is 0x5449.
 * \return The manufacturer ID (0x5449).
 */
uint16_t OPT3002::readManufacturerID()
{
    return _readRegister(OPT3002_REGISTER_ID);
}

// ============================================================
/*!
 * \brief Read and return the configuration register.
 * \return The content of the configuration register.
 */
uint16_t OPT3002::readConfiguration()
{
	return _readRegister(OPT3002_REGISTER_CONFIG);
}

// ============================================================
/*!
 * \brief Read result register, calc and return the real value.
 * \return float result : The last value mesured.
 */
float OPT3002::readResult()
{
	uint16_t raw = _readRegister(OPT3002_REGISTER_RESULT);
	USB.println(raw, HEX);
	uint16_t exponent = ((raw & 0xF000) >> 12);
	uint16_t fractional = (raw & 0x0FFF);
	return (1.2f)*(fractional)*(pow(2,exponent));
}

// ============================================================
/*!
 * \brief Return the low limit.
 * \return float : The actual low limit.
 */
float OPT3002::readLowLimit()
{
	uint16_t raw = _readRegister(OPT3002_REGISTER_LIMIT_LOW);
	uint16_t exponent = ((raw & 0xF000) >> 12);
	uint16_t fractional = (raw & 0x0FFF);
	return (1.2f)*(fractional)*(pow(2,exponent));
}

// ============================================================
/*!
 * \brief Return the high limit.
 * \return float : The actual high limit.
 */
float OPT3002::readHighLimit()
{
	uint16_t raw = _readRegister(OPT3002_REGISTER_LIMIT_HIGH);
	uint16_t exponent = ((raw & 0xF000) >> 12);
	uint16_t fractional = (raw & 0x0FFF);
	return (1.2f)*(fractional)*(pow(2,exponent));
}

// ============================================================
/*!
 * \brief Read a single register of 16 bits.
 * \param uint8_t reg : The address of the register to read.
 *                - OPT3002_REGISTER_RESULT
 *                - OPT3002_REGISTER_CONFIG
 *                - OPT3002_REGISTER_LIMIT_LOW
 *                - OPT3002_REGISTER_LIMIT_HIGH
 *                - OPT3002_REGISTER_ID
 * \return uint16_t content : The content of the register.
 */
uint16_t OPT3002::_readRegister(uint8_t reg)
{
    uint8_t buffer[2];
    I2C.read(_address, reg, buffer, 2);
	uint16_t content = (buffer[0] << 8);
	content += buffer[1];
    return content;
}

