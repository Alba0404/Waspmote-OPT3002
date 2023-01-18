/*  
 *  Explanation: This example shows how to get the vale of light
 *  sensor. Sensor OPT3002 connected to the I2C bus.
 *  
 *  Copyright (C) 2023 Alba0404 
 *  
 *  This program is free software: you can redistribute it and/or modify 
 *  it under the terms of the GNU General Public License as published by 
 *  the Free Software Foundation, either version 3 of the License, or 
 *  (at your option) any later version. 
 *  
 *  This program is distributed in the hope that it will be useful, 
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 *  GNU General Public License for more details. 
 *  
 *  You should have received a copy of the GNU General Public License 
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 *  
 *  Version:    1.0 
 *  Author:     Alba0404
 */

#include <OPT3002.h>

OPT3002 sensor;

void setup()
{
  // Start the sensor with the default address.
  sensor.ON(OPT3002_I2C_ADDR_GND);
}


void loop()
{
  USB.ON();
  
  uint16_t id = sensor.readManufacturerID();
  USB.print("Manufacturer ID: 0x");
  USB.println(id, HEX);
  
  USB.print("Configuration: ");
  USB.println(sensor.readConfiguration(), BIN);

  USB.print("Value: ");
  USB.println(sensor.readResult());

  USB.print("Low limit: ");
  USB.println(sensor.readLowLimit());

  USB.print("High limit: ");
  USB.println(sensor.readHighLimit());
  
  USB.println();
  USB.OFF();
  delay(3000);
}
