# ble_i2c_mma7660_nrf

In this project I have interfaced accelerometer sensor - MMA7660 with nrf development board using I2C protocol.

I have written a separate library MMA7660.c for i2c implementation.(This example is different from the given example on MMA7660 in the sdk)

sdk version : 15.0.0 , 
SoC : nrf52832 

Do the necessary changes if you are using a different version. Mainly in flash_placement.xml file and sdk_config.h
