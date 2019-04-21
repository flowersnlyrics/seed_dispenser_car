/*******************************************************************************
* @file           : accel_ctrl.c
* @brief          : 
*******************************************************************************/
/* ----------------------------------------------------------------- Includes */
#include "accel_ctrl.h"

/* ------------------------------------------------------ Private Definitions */
#define LSM9DS1_ACCEL_MG_LSB_4G (0.122f)
#define MG_PER_G                (1000.0f)

typedef enum 
{
  FS_GRAV_2G = 0, 
  FS_GRAV_4G, 
  FS_GRAV_8G, 
  FS_GRAV_16G, 
  NUM_GRAV_FS
} fs_grav_t; 

typedef enum 
{
  POWER_DOWN, 
  ODR_10_HZ, 
  ODR_50_HZ, 
  ODR_119_HZ,  
  ODR_238_HZ,
  ODR_476_HZ, 
  ODR_952_HZ,
  NUM_XL_ODRS
} odr_xl_t; 

/* ---------------------------------------------- Private Function Prototypes */
static bool set_full_scale(fs_grav_t fs); 
static bool set_axis_enable(axis_t axis, bool en); 
static bool set_odr(odr_xl_t odr); 
static float read_to_float(uint8_t msb, uint8_t lsb); 

/* ---------------------------------------------- Public Function Definitions */


/******************************************************************************
 * @fn      accel_ctrl_init
 * @brief  
 * @return  
 ******************************************************************************/
bool accel_ctrl_init(void)
{
  if(!accel_if_init())
  {
    return false; 
  }
  
  /* Set full scale to +/- a fs_grav_t setting */
  if(!set_full_scale(FS_GRAV_4G))
  {
    return false; 
  }
  
  /* Set output enable for all axis */
  for(axis_t axis=X_AXIS; axis < NUM_AXES; axis++)
  {
    if(!set_axis_enable(axis, true))
    {
      return false; 
    }
  }
  
  /* Set the Output Data Rate */
  if(!set_odr(ODR_952_HZ))
  {
    return false; 
  }
  
  return true; 
}

/******************************************************************************
 * @fn      accel_ctrl_get_read
 * @brief  
 * @param 
 * @return  
 ******************************************************************************/
bool accel_ctrl_get_read(accel_read_t* read)
{
  uint8_t buff[NUM_AXES * 2]; 
  accel_reg_t addrs[NUM_AXES * 2] = { OUT_X_L_XL,
                                      OUT_X_H_XL,
                                      OUT_Y_L_XL,
                                      OUT_Y_H_XL, 
                                      OUT_Z_L_XL,
                                      OUT_Z_H_XL}; 
  uint8_t status_1 ; 
  
  do
  {
    accel_if_read_reg(STATUS_1, &status_1);
  } while(status_1 & 0x01 != 0x01);
  
  for(int i = 0; i < (NUM_AXES *2); i++)
  {
    if(!accel_if_read_reg(addrs[i], &buff[i]))
    {
      return false; 
    }
  }
 
  read->x = read_to_float(buff[1], buff[0]) * LSM9DS1_ACCEL_MG_LSB_4G ;
  read->x /= MG_PER_G;
  
  read->y = read_to_float(buff[3], buff[2]) * LSM9DS1_ACCEL_MG_LSB_4G ;
  read->y /= MG_PER_G;
  
  read->z = read_to_float(buff[5], buff[4]) * LSM9DS1_ACCEL_MG_LSB_4G ;
  read->z /= MG_PER_G;
  
  return true; 
  
}

/* Private Function Definitions */

/******************************************************************************
 * @fn      set_full_scale
 * @brief  
 * @param
 * @return  
 ******************************************************************************/
static bool set_full_scale(fs_grav_t fs)
{
  uint8_t msk = 0x00, ctrl_reg6_xl = 0x00; 
  
  switch(fs)
  {
    case FS_GRAV_2G:
      msk = 0x00; 
      break; 
    case FS_GRAV_4G:
      msk = CTRL_REG6_XL_FS_XL_PM_4G;
      break;  
    case FS_GRAV_8G:
      msk = CTRL_REG6_XL_FS_XL_PM_8G;
      break;  
    case FS_GRAV_16G:
      msk = CTRL_REG6_XL_FS_XL_PM_16G;
      break;     
    default:
      return false; 
  }
  
  if(accel_if_read_reg(CTRL_REG6_XL, &ctrl_reg6_xl))
  {
    ctrl_reg6_xl &= ~CTRL_REG6_XL_FS_XL_Msk; 
    ctrl_reg6_xl |= msk; 
    
    if(accel_if_write_reg(CTRL_REG6_XL, &ctrl_reg6_xl))
    {
      // TODO delete afte debugging
      accel_if_read_reg(CTRL_REG6_XL, &ctrl_reg6_xl);
      return true; 
    }
  }

  return false; 
}

/******************************************************************************
 * @fn      set_full_scale
 * @brief  
 * @param   axis: adjust output enable for which axis
 * @param   en: output enable desired value 
 * @return  
 ******************************************************************************/
static bool set_axis_enable(axis_t axis, bool en)
{
  uint8_t enables[NUM_AXES] = {CTRL_REG5_XL_Xen_XL_ENABLE,
                               CTRL_REG5_XL_Yen_XL_ENABLE,
                               CTRL_REG5_XL_Zen_XL_ENABLE};
  uint8_t en_msks[NUM_AXES] = {CTRL_REG5_XL_Xen_XL_Msk, 
                               CTRL_REG5_XL_Yen_XL_Msk,
                               CTRL_REG5_XL_Zen_XL_Msk};
  uint8_t ctrl_reg5;
  
  if(!accel_if_read_reg(CTRL_REG5_XL, &ctrl_reg5))
  {
    return false; 
  }
  
  ctrl_reg5 &= ~en_msks[axis]; 
  
  if(en)
  {
    ctrl_reg5 |= enables[axis]; 
  }
  
  if(!accel_if_write_reg(CTRL_REG5_XL, &ctrl_reg5))
  {
    return false; 
  }
  
  // TODO delete after debugging
  accel_if_read_reg(CTRL_REG5_XL, &ctrl_reg5);
  return true; 
}

/******************************************************************************
 * @fn      set_odr
 * @brief  
 * @param   odr: <o>utput <d>ata <r>ate 
 * @param   
 * @return  
 ******************************************************************************/
static bool set_odr(odr_xl_t odr)
{
  uint8_t msk = 0x00, ctrl_reg6; 
  
  switch(odr)
  {
  case POWER_DOWN:
    msk = 0x00; 
    break; 
  case ODR_10_HZ:
    msk = CTRL_REG6_XL_ODR_XL_10_HZ;
    break;  
  case ODR_50_HZ:
    msk = CTRL_REG6_XL_ODR_XL_50_HZ;
    break;  
  case ODR_119_HZ:
    msk = CTRL_REG6_XL_ODR_XL_119_HZ;
    break;   
  case ODR_238_HZ:
    msk = CTRL_REG6_XL_ODR_XL_238_HZ;
    break; 
  case ODR_476_HZ:
    msk = CTRL_REG6_XL_ODR_XL_476_HZ;
    break;  
  case ODR_952_HZ:
    msk = CTRL_REG6_XL_ODR_XL_952_HZ;
    break; 
  default:
    return false; 
  }
  
  if(!accel_if_read_reg(CTRL_REG6_XL, &ctrl_reg6))
  {
    return false; 
  }
  
  ctrl_reg6 &= ~CTRL_REG6_XL_ODR_XL_Msk ; 
  ctrl_reg6 |= msk; 
  
  if(accel_if_write_reg(CTRL_REG6_XL, &ctrl_reg6))
  {
    // TODO delete after debugging 
    accel_if_read_reg(CTRL_REG6_XL, &ctrl_reg6);
    return true; 
  }
  
  // TODO delete after debuggin (return the write return) 
  return true; 
  
}

/******************************************************************************
 * @fn      read_to_float
 * @brief  
 * @param   
 * @param   
 * @return  
 ******************************************************************************/
static float read_to_float(uint8_t msb, uint8_t lsb)
{
  uint16_t tmp;
  bool neg = false; 
  float ret; 
  
  tmp = (msb << 8) | lsb;
  
  if(msb & 0x80)
  {
    neg = true; 
    tmp = ~tmp + 1;
  }
  
  ret = neg ? (-1.0f * (float)(tmp)) : (float)(tmp);

  return ret; 
}

/******************************************************************************
 * @fn      accel_test
 * @brief  
 ******************************************************************************/
void accel_test(void)
{
  uint8_t  WHO_IS_XG = 0x01; 
  accel_if_read_reg(WHO_AM_I_XG, &WHO_IS_XG); 
}