

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
// LTC2492 I2C HAL
#define I2C_READ  Wire.read  
#define I2C_WRITE Wire.write
#endif


// LTC2492 address
#define LTC2942_ADDR 0x64

// LTC2942 register definitions
#define REG_LTC2942_STATUS   (uint8_t)0x00  // (A) Status 
#define REG_LTC2942_CONTROL  (uint8_t)0x01  // (B) Control
#define REG_LTC2942_AC_H     (uint8_t)0x02  // (C) Accumulated Charge MSB
#define REG_LTC2942_AC_L     (uint8_t)0x03  // (D) Accumulated Charge LSB
#define REG_LTC2942_CTH_H    (uint8_t)0x04  // (E) Charge Threshold High MSB
#define REG_LTC2942_CTH_L    (uint8_t)0x05  // (F) Charge Threshold High LSB
#define REG_LTC2942_CTL_H    (uint8_t)0x06  // (G) Charge Threshold Low MSB
#define REG_LTC2942_CTL_L    (uint8_t)0x07  // (H) Charge Threshold Low LSB
#define REG_LTC2942_V_H      (uint8_t)0x08  // (I) Voltage MSB
#define REG_LTC2942_V_L      (uint8_t)0x09  // (J) Voltage LSB
#define REG_LTC2942_VT_H     (uint8_t)0x0A  // (K) Voltage Threshold MSB
#define REG_LTC2942_VT_L     (uint8_t)0x0B  // (L) Voltage Threshold LSB
#define REG_LTC2942_T_H      (uint8_t)0x0C  // (M) Temperature MSB
#define REG_LTC2942_T_L      (uint8_t)0x0D  // (N) Temperature LSB
#define REG_LTC2942_TT_H     (uint8_t)0x0E  // (O) Temperature Threshold MSB
#define REG_LTC2942_TT_L     (uint8_t)0x0F  // (P) Temperature Threshold LSB

// LTC2492 REG_LTC2942_STATUS Bit Mask (BITM) and Bit Position (BITP)
#define BITM_REG_LTC2942_STATUS_UVLO (uint8_t)0x01  // A[0]
#define BITP_REG_LTC2942_STATUS_UVLO 0

#define BITM_REG_LTC2942_STATUS_VA (uint8_t)0x02  // A[1]
#define BITP_REG_LTC2942_STATUS_VA 1

#define BITM_REG_LTC2942_STATUS_CAL (uint8_t)0x04  // A[2]
#define BITP_REG_LTC2942_STATUS_CAL 2

#define BITM_REG_LTC2942_STATUS_CAH (uint8_t)0x08  // A[3]
#define BITP_REG_LTC2942_STATUS_CAH 3

#define BITM_REG_LTC2942_STATUS_TA (uint8_t)0x10  // A[4]
#define BITP_REG_LTC2942_STATUS_TA 4

#define BITM_REG_LTC2942_STATUS_ACOU (uint8_t)0x20  // A[5]
#define BITP_REG_LTC2942_STATUS_ACOU 5

#define BITM_REG_LTC2942_STATUS_CI (uint8_t)0x80  // A[6]
#define BITP_REG_LTC2942_STATUS_CI 7


// LTC2492 REG_LTC2942_CONTROL Bit Mask (BITM) and Bit Position (BITP)
#define BITM_REG_LTC2942_CONTROL_SHUTDOWN (uint8_t)0x01  // B[0]
#define BITP_REG_LTC2942_CONTROL_SHUTDOWN 0

#define BITM_REG_LTC2942_CONTROL_ALCC (uint8_t)0x06  // B[2:1]
#define BITP_REG_LTC2942_CONTROL_ALCC 1

#define BITM_REG_LTC2942_CONTROL_PM (uint8_t)0x38  // B[5:3]
#define BITP_REG_LTC2942_CONTROL_PM 3

#define BITM_REG_LTC2942_CONTROL_ADCM (uint8_t)0xC0  // B[7:6]
#define BITP_REG_LTC2942_CONTROL_ADCM 6


// LTC2942 ADC mode enumeration
enum 
{
    LTC2942_ADC_AUTO   = (uint8_t)0x03, // Automatic mode
    LTC2942_ADC_M_VOL  = (uint8_t)0x02, // Manual voltage mode
    LTC2942_ADC_M_TEMP = (uint8_t)0x01, // Manual temperature mode
    LTC2942_ADC_SLEEP  = (uint8_t)0x00  // Sleep
};

// LTC2942 prescaler M enumeration
enum 
{
    LTC2942_PSCM_1   = (uint8_t)0x00,
    LTC2942_PSCM_2   = (uint8_t)0x08,
    LTC2942_PSCM_4   = (uint8_t)0x10,
    LTC2942_PSCM_8   = (uint8_t)0x18,
    LTC2942_PSCM_16  = (uint8_t)0x20,
    LTC2942_PSCM_32  = (uint8_t)0x28,
    LTC2942_PSCM_64  = (uint8_t)0x30,
    LTC2942_PSCM_128 = (uint8_t)0x38
};

// LTC2942 AL/CC pin mode enumeration
enum 
{
    LTC2942_ALCC_DISABLED = (uint8_t)0x00, // AL/CC pin disabled
    LTC2942_ALCC_CHG      = (uint8_t)0x02, // Charge complete mode
    LTC2942_ALCC_ALERT    = (uint8_t)0x04  // Alert mode
};

class Battery_Gauge
{
public:
    Battery_Gauge();
    
    //uint8_t  get_status();
    //uint8_t  get_control();
    //float    get_temperature();
    uint32_t get_voltage();
    
    unsigned char get_register(unsigned char reg_addr);
    void set_register(unsigned char reg_addr, unsigned char reg_value);
};

