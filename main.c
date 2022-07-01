
#include <stdio.h>
#include "boards.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nrf_delay.h"

#include "mma7660.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"


static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

// A flag to indicate the transfer state
static volatile bool m_xfer_done = false;


/**
 * @brief Function for main application entry.
 */
int main(void)
{
    ret_code_t err_code;
    uint8_t address;
    uint8_t sample_data;
    bool detected_device = false;

    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();

    NRF_LOG_INFO("TWI scanner started.");
    NRF_LOG_FLUSH();
    twi_init();

    for (address = 1; address <= TWI_ADDRESSES; address++)
    {
        err_code = nrf_drv_twi_rx(&m_twi, address, &sample_data, sizeof(sample_data));
        if (err_code == NRF_SUCCESS)
        {
            detected_device = true;
            NRF_LOG_INFO("TWI device detected at address 0x%x.", address);
        }
        NRF_LOG_FLUSH();
    }

    if (!detected_device)
    {
        NRF_LOG_INFO("No device was found.");
        NRF_LOG_FLUSH();
    }
    static int8_t AccValue[3];
    
   // bsp_board_init(BSP_INIT_LEDS | BSP_INIT_BUTTONS); // initialize the leds and buttons

   // nrf_delay_ms(1000); // give some delay

    while(mma7660_init() == false) // wait until MMA7660 sensor is successfully initialized
    {
      NRF_LOG_INFO("MMA7660 initialization failed!!!"); // if it failed to initialize then print a message
      nrf_delay_ms(1000);
    }

   NRF_LOG_INFO("MMA7660 Init Successfully!!!"); 

   NRF_LOG_INFO("Reading Values from ACC "); // display a message to let the user know that the device is starting to read the values
   nrf_delay_ms(2000);


  
    
    while (true)
    {
        if(MMA7660_ReadCord(&AccValue[0], &AccValue[1], &AccValue[2]) == true) // Read acc value from MMA7660 internal registers and save them in the array
        {
          NRF_LOG_INFO("Coordinates:  x = %d  y = %d  z = %d\n", AccValue[0], AccValue[1], AccValue[2]); // display the read values
          printf("Coordinates:  x = %d  y = %d  z = %d", AccValue[0], AccValue[1], AccValue[2]);
        }
        else
        {
          NRF_LOG_INFO("Reading cordinates Failed!!!"); // if reading was unsuccessful then let the user know about it
        }


       
       nrf_delay_ms(100); // give some delay 


    }

    while (true)
    {
        /* Empty loop. */
    }
}

/** @} */