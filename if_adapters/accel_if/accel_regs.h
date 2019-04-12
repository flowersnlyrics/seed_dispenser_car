#ifndef __ACCEL_REGS_H__
#define __ACCEL_REGS_H__


/* ----------------------------------- Accelerometer read and write addresses */
#define ACCEL_I2C_READ_ADDR     0xD7
#define ACCEL_I2C_WRITE_ADDR    0xD6
#define SIZE_OF_REGISTER        0x01 // byte 
#define SIZE_OF_REGISTER_ADDR   0x01 // byte 

/* ------------------------------- Accelerometer Register Address Definitions */
#define ACT_THS_ADDR                 0x04
#define ACT_DUR_ADDR                 0x05
#define INT_GEN_CFG_XL_ADDR          0x06
#define INT_GEN_THS_X_XL_ADDR        0x07
#define INT_GEN_THS_Y_XL_ADDR        0x08
#define INT_GEN_THS_Z_XL_ADDR        0x09    
#define INT_GEN_DUR_XL_ADDR          0x0A
#define REFERENCE_G_ADDR             0x0B
#define INT1_CTRL_ADDR               0x0C
#define INT2_CTRL_ADDR               0x0D        
#define WHO_AM_I_XG_ADDR             0x0F
#define CTRL_REG1_G_ADDR             0x10
#define CTRL_REG2_G_ADDR             0x11
#define CTRL_REG3_G_ADDR             0x12
#define ORIENT_CFG_G_ADDR            0x13
#define INT_GEN_SRC_G_ADDR           0x14
#define OUT_TEMP_L_ADDR              0x15
#define OUT_TEMP_H_ADDR              0x16
#define STATUS_REG_0_ADDR            0x17
#define OUT_X_L_G_ADDR               0x18
#define OUT_X_H_G_ADDR               0x19
#define OUT_Y_L_G_ADDR               0x1A
#define OUT_Y_H_G_ADDR               0x1B
#define OUT_Z_L_G_ADDR               0x1C
#define OUT_Z_H_G_ADDR               0x1D
#define CTRL_REG4_ADDR               0x1E
#define CTRL_REG5_XL_ADDR            0x1F
#define CTRL_REG6_XL_ADDR            0x20
#define CTRL_REG7_XL_ADDR            0x21
#define CTRL_REG8_ADDR               0x22
#define CTRL_REG9_ADDR               0x23
#define CTRL_REG10_ADDR              0x24
#define INT_GEN_SRC_XL_ADDR          0x26
#define STATUS_REG_1_ADDR            0x27
#define OUT_X_L_XL_ADDR              0x28
#define OUT_X_H_XL_ADDR              0x29
#define OUT_Y_L_XL_ADDR              0x2A
#define OUT_Y_H_XL_ADDR              0x2B
#define OUT_Z_L_XL_ADDR              0x2C
#define OUT_Z_H_XL_ADDR              0x2D
#define FIFO_CTRL_ADDR               0x2E
#define FIFO_SRC_ADDR                0x2F
#define INT_GEN_CFG_G_ADDR           0x30 
#define INT_GEN_THS_XH_G_ADDR        0x31
#define INT_GEN_THS_XL_G_ADDR        0x32
#define INT_GEN_THS_YH_G_ADDR        0x33
#define INT_GEN_THS_YL_G_ADDR        0x34
#define INT_GEN_THS_ZH_G_ADDR        0x35
#define INT_GEN_THS_ZL_G_ADDR        0x36
#define INT_GEN_DUR_G_ADDR           0x37

/* ---------------------------------------------- Bitmasks for CTRL_REG8 0x22 */

#define CTRL_REG8_SW_RESET_Pos		(0U)		                        /*!<Software reset */
#define CTRL_REG8_SW_RESET_Msk		(0x1U << CTRL_REG8_SW_RESET_Pos)	/*!<Mask */
#define CTRL_REG8_SW_RESET_RESET	(0x1U << CTRL_REG8_SW_RESET_Pos)	/*!<0x0001 */

#define CTRL_REG8_IF_ADD_INC_Pos	(2U)		                        /*!<Reg addr increments automatically */
#define CTRL_REG8_IF_ADD_INC_Msk	(0x1U << CTRL_REG8_IF_ADD_INC_Pos)	/*!<Mask */
#define CTRL_REG8_IF_ADD_INC_EN	        (0x1U << CTRL_REG8_IF_ADD_INC_Pos)	/*!<0x0004 */

#endif /* __ACCEL_REGS_H__ */

