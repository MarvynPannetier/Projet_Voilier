
#include "envoi_donnees.h"
#include "stm32f1xx_ll_gpio.h"
#include "GPIO.h"
#include "stm32f1xx_ll_usart.h" 
#include "UART.h"

/**
	* @brief  Configuration des IO en Output 
  * @note   PA11 en alternate Push-Pull et PA9 en Push-Pull
	* @param  
  * @retval Aucun
  */

void config_envoi(void) {
	

	//Configuration PA9 et PA11
		
		GPIO_output_conf(GPIOA,  LL_GPIO_PIN_9, LL_GPIO_MODE_ALTERNATE, LL_GPIO_SPEED_FREQ_LOW, LL_GPIO_OUTPUT_PUSHPULL);
	  GPIO_output_conf(GPIOA,  LL_GPIO_PIN_11, LL_GPIO_MODE_OUTPUT, LL_GPIO_SPEED_FREQ_LOW, LL_GPIO_OUTPUT_PUSHPULL);

	  USART1_Conf();
		
	}


