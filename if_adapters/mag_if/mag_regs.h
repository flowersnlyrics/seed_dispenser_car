#ifndef __MAG_REGS_H__
#define __MAG_REGS_H__


/* ------------------------------------ Magnetometer read and write addresses */
#define MAG_I2C_READ_ADDR     0x3D
#define MAG_I2C_WRITE_ADDR    0x3C
#define SIZE_OF_MAG_REGISTER      0x01 // byte 
#define SIZE_OF_MAG_REGISTER_ADDR 0x01 // BYTE

/* -------------------------------- Magnetometer Register Address Definitions */
#define OFFSET_X_REG_L_M_ADDR                0x05
#define OFFSET_X_REG_H_M_ADDR                0x06
#define OFFSET_Y_REG_L_M_ADDR                0x07
#define OFFSET_Y_REG_H_M_ADDR                0x08
#define OFFSET_Z_REG_L_M_ADDR                0x09
#define OFFSET_Z_REG_H_M_ADDR                0x0A
#define WHO_AM_I_M_ADDR                      0x0F
#define CTRL_REG1_M_ADDR                     0x20
#define CTRL_REG2_M_ADDR                     0x21    
#define CTRL_REG3_M_ADDR                     0x22
#define CTRL_REG4_M_ADDR                     0x23
#define CTRL_REG5_M_ADDR                     0x24
#define STATUS_REG_M_ADDR                    0x27        
#define OUT_X_L_M_ADDR                       0x28
#define OUT_X_H_M_ADDR                       0x29
#define OUT_Y_L_M_ADDR                       0x2A
#define OUT_Y_H_M_ADDR                       0x2B
#define OUT_Z_L_M_ADDR                       0x2C
#define OUT_Z_H_M_ADDR                       0x2D
#define INT_CFG_M_ADDR                       0x30
#define INT_SRC_M_ADDR                       0x31
#define INT_THS_L_M_ADDR                     0x32
#define INT_THS_H_M_ADDR                     0x33

/* -------------------------------------------- Bitmasks for CTRL_REG2_M 0x21 */

#define CTRL_REG2_M_REBOOT_Pos		(3U)		                        /*!<Reboot memory content */
#define CTRL_REG2_M_REBOOT_Msk		(0x1U << CTRL_REG2_M_REBOOT_Pos)	/*!<Mask */
#define CTRL_REG2_M_REBOOT_REBOOT	(0x1U << CTRL_REG2_M_REBOOT_Pos)	/*!<0x0008 */

#define CTRL_REG2_M_SOFT_RST_Pos	(2U)		                        /*!<reset config/user registers */
#define CTRL_REG2_M_SOFT_RST_Msk	(0x1U << CTRL_REG2_M_SOFT_RST_Pos)	/*!<Mask */
#define CTRL_REG2_M_SOFT_RST_RESET	(0x1U << CTRL_REG2_M_SOFT_RST_Pos)	/*!<0x0004 */


#endif /* __MAG_REGS_H__ */

