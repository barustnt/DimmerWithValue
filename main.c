
/** @file
 * @defgroup pwm_example_main main.c
 * @{
 * @ingroup pwm_example
 *
 * @brief  PWM Example Application main file.
 *
 * This file contains the source code for a sample application using PWM.
 *
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "app_error.h"
#include "bsp.h"
#include "nrf_delay.h"
#include "app_pwm.h"


APP_PWM_INSTANCE(PWM2,2);                   // Create the instance "PWM2" using TIMER2.
	
static volatile bool ready_flag;            // A flag indicating PWM status.

void pwm_ready_callback(uint32_t pwm_id)    // PWM callback function
{
    ready_flag = true;
}

int main(void)
{
   ret_code_t err_code;

    /* 2-channel PWM2, 200Hz, output on  LED pin. */
   
	
    app_pwm_config_t pwm2_cfg =APP_PWM_DEFAULT_CONFIG_1CH 	( 5000L	,21	) ;		// 21 pin number on bicon  5000L periode on us 
	  
		
    /* Switch the polarity of the second channel. */
    pwm2_cfg.pin_polarity[1] = APP_PWM_POLARITY_ACTIVE_HIGH;

    /* Initialize and enable PWM. */
    err_code = app_pwm_init(&PWM2,&pwm2_cfg,pwm_ready_callback);
    APP_ERROR_CHECK(err_code);
    app_pwm_enable(&PWM2);

    uint32_t value;
    while (true)
    {
        
             value = 20; //value on % of our LED

            ready_flag = false;
            /* Set the duty cycle - keep trying until PWM is ready... */
            while (app_pwm_channel_duty_set(&PWM2, 0, value) == NRF_ERROR_BUSY);

            /* ... or wait for callback. */
            while (!ready_flag);
            APP_ERROR_CHECK(app_pwm_channel_duty_set(&PWM2, 1, value));
          
        
    }

}


/** @} */
