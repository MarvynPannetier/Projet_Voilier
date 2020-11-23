//GPIO;


#include "GPIO.h"
#include "stm32f1xx_ll_gpio.h"




// -------------------------- Gestion de l'index de la girouette -------------------------------// 

/**
	* @brief  Configuration de l'IO PA5 en Floating input pour la gestion de l'index de la girouette 
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void GPIO_input_conf(GPIO_TypeDef *GPIOx, uint32_t pin, uint32_t mode, uint32_t speed)
{
	LL_GPIO_SetPinMode(GPIOx,pin,mode);
	LL_GPIO_SetPinSpeed(GPIOx,pin,speed);
}
	
void GPIO_output_conf(GPIO_TypeDef *GPIOx, uint32_t pin , uint32_t mode, uint32_t speed, uint32_t output_type)
{
	
	
	LL_GPIO_SetPinMode(GPIOx,pin,mode);
	LL_GPIO_SetPinSpeed(GPIOx,pin,speed);
	LL_GPIO_SetPinOutputType(GPIOx,pin,output_type);
	
		
}
