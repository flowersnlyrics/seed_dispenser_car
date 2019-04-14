/*******************************************************************************
* @file           : accel_ctrl.c
* @brief          : 
*******************************************************************************/
/* ----------------------------------------------------------------- Includes */
#include "accel_ctrl.h"

/* ------------------------------------------------------ Private Definitions */
typedef enum 
{
  FS_GRAV_2G = 0, 
  FS_GRAV_4G, 
  FS_GRAV_8G, 
  FS_GRAV_16G, 
  NUM_GRAV_FS
} fs_grav_t; 

/* ---------------------------------------------- Private Function Prototypes */
static bool set_full_scale(fs_grav_t fs); 
static bool set_axis_enable(axis_t axis, bool en); 

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
  
  for(axis_t axis=X_AXIS; axis < NUM_AXES; axis++)
  {
    if(!set_axis_enable(axis, true))
    {
      return false; 
    }
  }
  
  return true; 
}

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


