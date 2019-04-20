/*******************************************************************************
* @file           : mag_ctrl.c
* @brief          : 
*******************************************************************************/
/* ----------------------------------------------------------------- Includes */
#include "mag_ctrl.h"

/* ------------------------------------------------------ Private Definitions */
typedef enum 
{
  FS_GAUSS_4G = 0, 
  FS_GAUSS_8G, 
  FS_GAUSS_12G, 
  FS_GAUSS_16G, 
  NUM_GAUSS_FS
} fs_gauss_t; 

/* ---------------------------------------------- Private Function Prototypes */
static bool set_full_scale(fs_gauss_t fs); 

/* ---------------------------------------------- Public Function Definitions */


/******************************************************************************
 * @fn      mag_ctrl_init
 * @brief  
 * @return  
 ******************************************************************************/
bool mag_ctrl_init(void)
{
  if(!mag_if_init())
  {
    return false; 
  }
   
  if(!set_full_scale(FS_GAUSS_4G))
  {
    return false; 
  }
  
  return true; 
}

/******************************************************************************
 * @fn      set_full_scale
 * @brief  
 * @param
 * @return  
 ******************************************************************************/
static bool set_full_scale(fs_gauss_t fs)
{
  uint8_t msk = 0x00, ctrl_reg2 = 0x00; 
  
  switch(fs)
  {
    case FS_GAUSS_4G:
      msk = 0x00; 
      break; 
    case FS_GAUSS_8G:
      msk = CTRL_REG2_M_FS_PM_8GAUSS;
      break;  
    case FS_GAUSS_12G:
      msk = CTRL_REG2_M_FS_PM_12GAUSS;
      break;  
    case FS_GAUSS_16G:
      msk = CTRL_REG2_M_FS_PM_16GAUSS;
      break;     
    default:
      return false; 
  }
  
  if(mag_if_read_reg(CTRL_REG2_M, &ctrl_reg2))
  {
    ctrl_reg2 &= ~CTRL_REG2_M_FS_Msk; 
    ctrl_reg2 |= msk; 
    
    if(mag_if_write_reg(CTRL_REG2_M, &ctrl_reg2))
    {
      // TODO delete afte debugging
      mag_if_read_reg(CTRL_REG2_M, &ctrl_reg2);
      return true; 
    }
  }

  return false; 
}

/******************************************************************************
 * @fn      mag_ctrl_test
 * @brief  
 * @return  
 ******************************************************************************/
void mag_ctrl_test(void)
{
  uint8_t WHO_IS_MAG = 0x01; 
  mag_if_read_reg(WHO_AM_I_M, &WHO_IS_MAG); 
}