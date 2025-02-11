#ifndef __LSM9DS1_DRVR_H
#define __LSM9DS1_DRVR_H

#include "spi.h"
#include "usart.h"

extern SPI_HandleTypeDef hspi1;

//Defines 
#define LSM9DS1_READ_MODE                  (0x01 << 7)
#define LSM9DS1_WRITE_MODE                 (0x00 << 7)
#define SPI_TIMEOUT                        1000

//Addresses
#define LSM9DS1_ADDRESS_ACCELGYRO          (0x6B)
#define LSM9DS1_ADDRESS_MAG                (0x1E)
#define LSM9DS1_XG_ID                      (0b01101000)
#define LSM9DS1_MAG_ID                     (0b00111101)

// Linear Acceleration: mg per LSB
#define LSM9DS1_ACCEL_MG_LSB_2G (0.061F)
#define LSM9DS1_ACCEL_MG_LSB_4G (0.122F)
#define LSM9DS1_ACCEL_MG_LSB_8G (0.244F)
#define LSM9DS1_ACCEL_MG_LSB_16G (0.732F) 

// Magnetic Field Strength: gauss range
#define LSM9DS1_MAG_MGAUSS_4GAUSS      (0.14F)
#define LSM9DS1_MAG_MGAUSS_8GAUSS      (0.29F)
#define LSM9DS1_MAG_MGAUSS_12GAUSS     (0.43F)
#define LSM9DS1_MAG_MGAUSS_16GAUSS     (0.58F)

// Angular Rate: dps per LSB
#define LSM9DS1_GYRO_DPS_DIGIT_245DPS      (0.00875F)
#define LSM9DS1_GYRO_DPS_DIGIT_500DPS      (0.01750F)
#define LSM9DS1_GYRO_DPS_DIGIT_2000DPS     (0.07000F)

// Temperature: LSB per degree celsius
#define LSM9DS1_TEMP_LSB_DEGREE_CELSIUS    (8)  // 1°C = 8, 25° = 200, etc.

#define MAGTYPE                           (true)
#define XGTYPE                            (false)

typedef enum
{
  LSM9DS1_REGISTER_WHO_AM_I_XG         = 0x0F,
  LSM9DS1_REGISTER_CTRL_REG1_G         = 0x10,
  LSM9DS1_REGISTER_CTRL_REG2_G         = 0x11,
  LSM9DS1_REGISTER_CTRL_REG3_G         = 0x12,
  LSM9DS1_REGISTER_TEMP_OUT_L          = 0x15,
  LSM9DS1_REGISTER_TEMP_OUT_H          = 0x16,
  LSM9DS1_REGISTER_STATUS_REG          = 0x17,
  LSM9DS1_REGISTER_OUT_X_L_G           = 0x18,
  LSM9DS1_REGISTER_OUT_X_H_G           = 0x19,
  LSM9DS1_REGISTER_OUT_Y_L_G           = 0x1A,
  LSM9DS1_REGISTER_OUT_Y_H_G           = 0x1B,
  LSM9DS1_REGISTER_OUT_Z_L_G           = 0x1C,
  LSM9DS1_REGISTER_OUT_Z_H_G           = 0x1D,
  LSM9DS1_REGISTER_CTRL_REG4           = 0x1E,
  LSM9DS1_REGISTER_CTRL_REG5_XL        = 0x1F,
  LSM9DS1_REGISTER_CTRL_REG6_XL        = 0x20,
  LSM9DS1_REGISTER_CTRL_REG7_XL        = 0x21,
  LSM9DS1_REGISTER_CTRL_REG8           = 0x22,
  LSM9DS1_REGISTER_CTRL_REG9           = 0x23,
  LSM9DS1_REGISTER_CTRL_REG10          = 0x24,

  LSM9DS1_REGISTER_OUT_X_L_XL          = 0x28,
  LSM9DS1_REGISTER_OUT_X_H_XL          = 0x29,
  LSM9DS1_REGISTER_OUT_Y_L_XL          = 0x2A,
  LSM9DS1_REGISTER_OUT_Y_H_XL          = 0x2B,
  LSM9DS1_REGISTER_OUT_Z_L_XL          = 0x2C,
  LSM9DS1_REGISTER_OUT_Z_H_XL          = 0x2D,

} lsm9ds1AccGyroRegisters_t;

typedef enum
{

  LSM9DS1_REGISTER_WHO_AM_I_M         = 0x0F,
  LSM9DS1_REGISTER_CTRL_REG1_M        = 0x20,
  LSM9DS1_REGISTER_CTRL_REG2_M        = 0x21,
  LSM9DS1_REGISTER_CTRL_REG3_M        = 0x22,
  LSM9DS1_REGISTER_CTRL_REG4_M        = 0x23,
  LSM9DS1_REGISTER_CTRL_REG5_M        = 0x24,
  LSM9DS1_REGISTER_STATUS_REG_M       = 0x27,
  LSM9DS1_REGISTER_OUT_X_L_M          = 0x28,
  LSM9DS1_REGISTER_OUT_X_H_M          = 0x29,
  LSM9DS1_REGISTER_OUT_Y_L_M          = 0x2A,
  LSM9DS1_REGISTER_OUT_Y_H_M          = 0x2B,
  LSM9DS1_REGISTER_OUT_Z_L_M          = 0x2C,
  LSM9DS1_REGISTER_OUT_Z_H_M          = 0x2D,
  LSM9DS1_REGISTER_CFG_M              = 0x30,
  LSM9DS1_REGISTER_INT_SRC_M          = 0x31,
} lsm9ds1MagRegisters_t;

typedef enum
{
  LSM9DS1_ACCELRANGE_2G                = (0x00 << 3),
  LSM9DS1_ACCELRANGE_16G               = (0x01 << 3),
  LSM9DS1_ACCELRANGE_4G                = (0x02 << 3),
  LSM9DS1_ACCELRANGE_8G                = (0x03 << 3),
} lsm9ds1AccelRange_t;

typedef enum
{
  LSM9DS1_ACCELDATARATE_POWERDOWN      = (0x00 << 4),
  LSM9DS1_ACCELDATARATE_3_125HZ        = (0x01 << 4),
  LSM9DS1_ACCELDATARATE_6_25HZ         = (0x02 << 4),
  LSM9DS1_ACCELDATARATE_12_5HZ         = (0x03 << 4),
  LSM9DS1_ACCELDATARATE_25HZ           = (0x04 << 4),
  LSM9DS1_ACCELDATARATE_50HZ           = (0x05 << 4),
  LSM9DS1_ACCELDATARATE_100HZ          = (0x06 << 4),
  LSM9DS1_ACCELDATARATE_200HZ          = (0x07 << 4),
  LSM9DS1_ACCELDATARATE_400HZ          = (0x08 << 4),
  LSM9DS1_ACCELDATARATE_800HZ          = (0x09 << 4),
  LSM9DS1_ACCELDATARATE_1600HZ         = (0x0A << 4)
} lm9ds1AccelDataRate_t;

typedef enum
{
  LSM9DS1_MAGGAIN_4GAUSS               = (0x00 << 5),  // +/- 4 gauss
  LSM9DS1_MAGGAIN_8GAUSS               = (0x01 << 5),  // +/- 8 gauss
  LSM9DS1_MAGGAIN_12GAUSS              = (0x02 << 5),  // +/- 12 gauss
  LSM9DS1_MAGGAIN_16GAUSS              = (0x03 << 5)   // +/- 16 gauss
} lsm9ds1MagGain_t;

typedef enum
{
  LSM9DS1_MAGDATARATE_3_125HZ          = (0x00 << 2),
  LSM9DS1_MAGDATARATE_6_25HZ           = (0x01 << 2),
  LSM9DS1_MAGDATARATE_12_5HZ           = (0x02 << 2),
  LSM9DS1_MAGDATARATE_25HZ             = (0x03 << 2),
  LSM9DS1_MAGDATARATE_50HZ             = (0x04 << 2),
  LSM9DS1_MAGDATARATE_100HZ            = (0x05 << 2)
} lsm9ds1MagDataRate_t;

typedef enum
{
  LSM9DS1_GYROSCALE_245DPS             = (0x00 << 3),  // +/- 245 degrees per second rotation
  LSM9DS1_GYROSCALE_500DPS             = (0x01 << 3),  // +/- 500 degrees per second rotation
  LSM9DS1_GYROSCALE_2000DPS            = (0x03 << 3)   // +/- 2000 degrees per second rotation
} lsm9ds1GyroScale_t;

/*! \enum
 *
 */
typedef enum
{
    LSM9DS1_OK, 
    LSM9DS1_INIT_ERR, 
} LSM9DS1_status_t; 


LSM9DS1_status_t LSM9DS1_driver_init(void);

LSM9DS1_status_t LSM9DS1_driver_write(uint8_t address, uint8_t *data, uint8_t size); 

LSM9DS1_status_t LSM9DS1_driver_read(uint8_t address, uint8_t *tx_buf, uint8_t *rx_buf, uint8_t num_bytes); 
#endif
