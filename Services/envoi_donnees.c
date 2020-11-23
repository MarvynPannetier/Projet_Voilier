
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

void envoi_donnees_conf() {
	

	//Configuration PA9 et PA11
		
		GPIO_output_conf(GPIOA,  LL_GPIO_PIN_9, LL_GPIO_MODE_ALTERNATE, LL_GPIO_SPEED_FREQ_LOW, LL_GPIO_OUTPUT_PUSHPULL);
	  GPIO_output_conf(GPIOA,  LL_GPIO_PIN_11, LL_GPIO_MODE_ALTERNATE, LL_GPIO_SPEED_FREQ_LOW, LL_GPIO_OUTPUT_PUSHPULL);

	  USART1_Conf();
		
	}



/**
	* @brief  envoi de la donnée par l'USART1 et gestion de TX
  * @note   baud rate = 9600 , 8 bits de données,1 bit de stop
	* @param  
  * @retval Aucun
  */
	
void envoi_donnee(char data){
		
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_11);      // on passe PA11 à 1 : début transmission
	
	USART1->DR |= data; 														  // Ecriture de la donnée dans le registre DR
	while(LL_USART_IsActiveFlag_TXE(USART1)==1) {}   	// Attente de la fin de transmission	
		
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_11);	  // on passe PA11 à 0 : trasmission terminée
	
	}
