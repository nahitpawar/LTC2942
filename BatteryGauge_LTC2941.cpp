#include <Wire.h>
#include "BatteryGauge_LTC2941.h"

float BatteryGauge::get_temperature()
{
    float bat_vol=0.0;
    uint8_t buf[2];
    
    // Trigger voltage measurement - Set ADC mode bits B[7:6] = 10
    set_register(REG_LTC2942_CONTROL, (get_register(REG_LTC2942_CONTROL) & !BITM_REG_LTC2942_CONTROL_ADCM) | (LTC2942_ADC_M_VOL << BITP_REG_LTC2942_CONTROL_ADCM) );
    
    // Read voltage value
    Wire.beginTransmission(LTC2942_ADDR);
    I2C_WRITE( (uint8_t)REG_LTC2942_V_H);  // set register pointer
    Wire.endTransmission();

    Wire.requestFrom(LTC2942_ADDR, 2);
    buf[0] = I2C_READ();
    buf[1] = I2C_READ();
    
    // Calculate measured voltage
    bat_vol = buf[1] | (buf[0] << 8);
    bat_vol *= 6000;
    bat_vol /= 65535;

    return bat_vol;
}

void BatteryGauge::set_register(unsigned char reg_addr, unsigned char reg_value)
{
    Wire.beginTransmission(LTC2942_ADDR);
    I2C_WRITE(reg_addr);  // set register pointer
    I2C_WRITE(reg_value);
    Wire.endTransmission();
}

unsigned char BatteryGauge::get_register(unsigned char reg_addr)
{
   unsigned char buf;
   Wire.beginTransmission(LTC2942_ADDR);
   I2C_WRITE( (uint8_t)reg_addr );                    // set register pointer
   Wire.endTransmission(false);
   
   Wire.requestFrom(LTC2942_ADDR, 1);

   while( Wire.available() == 0 );
   return I2C_READ();
}

BatteryGauge::BatteryGauge()
{
}


