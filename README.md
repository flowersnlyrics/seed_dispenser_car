# Automatic Seed Dispenser Car
Final project for SE740 Vision, Robotics & Control <br/>
Spring 2019 @ Boston University  <br/>

# Getting Started
## Hardware Needed
+ OSOYOO Robot Smart Car [Kit](https://www.amazon.com/dp/B074Z6DMYP/ref=cm_sw_em_r_mt_dp_U_9QwMCbNGRHGH2) 
  - All we need here are a few components
    - car chassi, four motors, four wheels 
    - [OSOYOO] (https://www.amazon.com/dp/B07FFT4CL4/ref=cm_sw_em_r_mt_dp_U_I21QCbEYR8BK4) Model-X motor control board 
  - Remove the Arduino UNO (not a powerful enough MCU) 
+ Two 18650, 3.7V, 3000mAh rechargeble batteries w/ charger (any brand) 
+ Adafruit [LSM9DS1](https://learn.adafruit.com/adafruit-lsm9ds1-accelerometer-+plus-gyro-plus-magnetometer-9-dof-breakout/overview) Accelerometer + Gyro + Magnetometer Breakout Board
+ OSOYOO [IR Obstacle Detector](https://www.amazon.com/OSOYOO-Infrared-Obstacle-Avoidance-Arduino/dp/B01I57HIJ0) - This will be used as a tachometer
+ [28BYJ-48](https://components101.com/motors/28byj-48-stepper-motor) - 5V Stepper Motor with the [ULN2003](https://www.electronicoscaldas.com/datasheet/ULN2003A-PCB.pdf) driver board (high current!)
+ [NUCLEO-L432KC](https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-mpu-eval-tools/stm32-mcu-mpu-eval-tools/stm32-nucleo-boards/nucleo-l432kc.html) Evaluation Board
+ [TXSO108E](https://www.addicore.com/TXS0108E-p/ad284.htm) 8-channel bidirectional level-shifters

## Software Needed 
- IAR Embedded Workbench 7.4 or later 
- STM32CubeMX 5.1.0 (or else you can't open this .ioc file)
- PuTTY, TeraTerm or similar terminal program 

