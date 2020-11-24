//UART;
#include "UART.h"
#include "stm32f1xx_ll_bus.h" // Pour l'activation des horloges
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_tim.h" 
#include "stm32f1xx_ll_usart.h" 
#include "GPIO.h"



	/**
	* @brief  Configuration de l'USART1
  * @note   baud rate = 9600 , 8 bits de données,1 bit de stop
	* @param  
  * @retval Aucun
  */
	
	void USART1_Conf() {
			
		
		// initialisation de la structure de type LL_USART_InitTypeDef 
		LL_USART_InitTypeDef My_LL_USART1; 	
		 
		
		
		My_LL_USART1.BaudRate = 9600;																	// on met 9600 en baud rate
		My_LL_USART1.Parity = LL_USART_PARITY_NONE;										// pas de bit de parité
		My_LL_USART1.DataWidth = LL_USART_DATAWIDTH_8B;								// 8 bit de données
		My_LL_USART1.StopBits = LL_USART_STOPBITS_1;									// 1 bit de stop
		My_LL_USART1.TransferDirection = LL_USART_DIRECTION_TX;				// TX est à 0 tant qu'il n'y a pas de transmission
		My_LL_USART1.HardwareFlowControl = LL_USART_HWCONTROL_NONE ;	// pas de contrôle de flux
		
		LL_USART_Init(USART1,&My_LL_USART1);
		
		// activation USART1
	  LL_USART_Enable(USART1);

		// Half duplex
		//LL_USART_EnableHalfDuplex(USART1);
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


