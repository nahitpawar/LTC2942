#include <Wire.h>
#include "BatteryGauge_LTC2941.h"

uint16_t  BatteryGauge::get_charge()
{
  uint32_t bat_charge=0;
  uint16_t CD_buf=0;
  uint8_t  buf[2];
  
  // Shutdown analog section (Set shutdown bit in control register - B[0] = 1) before charge measurement
  //set_register( REG_LTC2942_CONTROL, ( get_register(REG_LTC2942_CONTROL) | BITM_REG_LTC2942_CONTROL_SHUTDOWN ) );

  // Read charge value
  Wire.beginTransmission(LTC2942_ADDR);
  I2C_WRITE( (uint8_t)REG_LTC2942_AC_H);  // set register pointer
  Wire.endTransmission(false);

  Wire.requestFrom(LTC2942_ADDR, 2);
  buf[0] = I2C_READ();  // Accumulated charge MSB
  buf[1] = I2C_READ();  // Accumulated charge LSB

  // Calculate battery charge from LTC2942 - I and J register 
  CD_buf = ( buf[1] | (buf[0] << 8) );

  // Enable analog section by clearing B[0] = 0 bit
  //set_register( REG_LTC2942_CONTROL, ( get_register(REG_LTC2942_CONTROL) & ~BITM_REG_LTC2942_CONTROL_SHUTDOWN ) );

  return CD_buf;
  
}

uint16_t BatteryGauge::get_voltage()
{
    uint32_t bat_vol=0;
    uint16_t IJ_buf=0;
    uint8_t  buf[2];

    //set_register( REG_LTC2942_CONTROL, ( get_register(REG_LTC2942_CONTROL) & ~BITM_REG_LTC2942_CONTROL_SHUTDOWN ) );

    //for(int i=0; i<1000; ++i);
    
    // Trigger voltage measurement - Set ADC mode bits B[7:6] = 10
    set_register(REG_LTC2942_CONTROL, ( get_register(REG_LTC2942_CONTROL) & ~BITM_REG_LTC2942_CONTROL_ADCM ) | ( LTC2942_ADC_M_VOL << BITP_REG_LTC2942_CONTROL_ADCM ) );
    
    for(int i=0; i<500; ++i);  // Small delay to wait for the converstion to complete - Ideally it should be 10ms
    
    // Read voltage value
    Wire.beginTransmission(LTC2942_ADDR);
    I2C_WRITE( (uint8_t)REG_LTC2942_V_H);  // set register pointer
    Wire.endTransmission(false);

    Wire.requestFrom(LTC2942_ADDR, 2);
    buf[0] = I2C_READ();  // Voltage MSB
    buf[1] = I2C_READ();  // Voltage LSB
    
    // Calculate measured voltage from LTC2942 - I and J register 
    IJ_buf = ( buf[1] | (buf[0] << 8) );
    bat_vol = ((uint32_t)IJ_buf * LTC2942_FULLSCALE_VOLTAGE);
    bat_vol >>= 16;

    //set_register( REG_LTC2942_CONTROL, ( get_register(REG_LTC2942_CONTROL) | BITM_REG_LTC2942_CONTROL_SHUTDOWN ) );

    return (uint16_t)bat_vol;
}

uint16_t BatteryGauge::get_temperature()
{
    uint32_t bat_temp=0;
    uint16_t MN_buf=0;
    uint8_t  buf[2];

    //set_register( REG_LTC2942_CONTROL, ( get_register(REG_LTC2942_CONTROL) & ~BITM_REG_LTC2942_CONTROL_SHUTDOWN ) );

    //for(int i=0; i<1000; ++i);
    
    // Trigger temperature measurement - Set ADC mode bits B[7:6] = 01
    set_register(REG_LTC2942_CONTROL, ( get_register(REG_LTC2942_CONTROL) & ~BITM_REG_LTC2942_CONTROL_ADCM ) | ( LTC2942_ADC_M_TEMP << BITP_REG_LTC2942_CONTROL_ADCM ) );
    
    for(int i=0; i<500; ++i);  // Small delay to wait for the converstion to complete - Ideally it should be 10ms
    
    // Read temperature value
    Wire.beginTransmission(LTC2942_ADDR);
    I2C_WRITE( (uint8_t)REG_LTC2942_T_H);  // set register pointer
    Wire.endTransmission(false);

    Wire.requestFrom(LTC2942_ADDR, 2);
    buf[0] = I2C_READ();  // Temperature MSB
    buf[1] = I2C_READ();  // Temperature LSB
    
    // Calculate measured temperature from LTC2942 - C and D register 
    MN_buf = ( buf[1] | (buf[0] << 8) );
    bat_temp = ((uint32_t)MN_buf * LTC2942_FULLSCALE_TEMPERATURE);
    bat_temp >>= 16;
    bat_temp -= 27315;  // Convert temperature from kelvin to degree celsius

    //set_register( REG_LTC2942_CONTROL, ( get_register(REG_LTC2942_CONTROL) | BITM_REG_LTC2942_CONTROL_SHUTDOWN ) );

    return (uint16_t)bat_temp;
}

void BatteryGauge::analog_off()
{
  set_register( REG_LTC2942_CONTROL, ( get_register(REG_LTC2942_CONTROL) | BITM_REG_LTC2942_CONTROL_SHUTDOWN ) );
}

void BatteryGauge::analog_on()
{
  set_register( REG_LTC2942_CONTROL, ( get_register(REG_LTC2942_CONTROL) & ~BITM_REG_LTC2942_CONTROL_SHUTDOWN ) );
  for(int i=0;i<1000;++i);
}

void BatteryGauge::set_register(unsigned char reg_addr, unsigned char reg_value)
{
    Wire.beginTransmission(LTC2942_ADDR);
    I2C_WRITE(reg_addr);                               // set register pointer
    I2C_WRITE(reg_value);
    Wire.endTransmission();
}

unsigned char BatteryGauge::get_register(unsigned char reg_addr)
{
   unsigned char buf;
   Wire.beginTransmission(LTC2942_ADDR);
   I2C_WRITE( (uint8_t)reg_addr );                    // set register pointer
   Wire.endTransmission(false);
   Wire.requestFrom(LTC2942_ADDR, 1);                 // request one byte from LTC294x
   while( Wire.available() == 0 );
   return I2C_READ();
}

BatteryGauge::BatteryGauge()
{
}


