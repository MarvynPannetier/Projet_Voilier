//UART;
//UART;
#include "UART.h"
#include "stm32f1xx_ll_bus.h" // Pour l'activation des horloges
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_tim.h" 
#include "stm32f1xx_ll_usart.h" 


/**
	* @brief  Configuration des IO en Output 
  * @note   PA11 en alternate Push-Pull et PA9 en Push-Pull
	* @param  
  * @retval Aucun
  */

void USART1_Conf_io() {
	
	//Configuration PA9 et PA11
		// activation de la clock du périphérique du port A lié à APB1
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA); 	
		
		// initialisation de la structure de type LL_GPIO_InitTypeDef 
		LL_GPIO_InitTypeDef My_LL_GPIOA_PA11; 	
		LL_GPIO_InitTypeDef My_LL_GPIOA_PA9; 	
		
		// Configuration en output Alternate PushPull --> Port A Pin 9 --> fréquence 20kHz
		My_LL_GPIOA_PA9.Pin=LL_GPIO_PIN_9;
		My_LL_GPIOA_PA9.Mode = LL_GPIO_MODE_ALTERNATE;
		My_LL_GPIOA_PA9.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
		My_LL_GPIOA_PA9.Speed=LL_GPIO_SPEED_FREQ_LOW;
	
	// Configuration en output  PushPull --> Port A Pin 11 --> fréquence 20kHz
		My_LL_GPIOA_PA11.Pin=LL_GPIO_PIN_11;
		My_LL_GPIOA_PA11.Mode = LL_GPIO_MODE_OUTPUT;
		My_LL_GPIOA_PA11.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
		My_LL_GPIOA_PA11.Speed=LL_GPIO_SPEED_FREQ_LOW;
	

		
		LL_GPIO_Init(GPIOA, &My_LL_GPIOA_PA9);
		LL_GPIO_Init(GPIOA, &My_LL_GPIOA_PA11);
	

		
	}

	/**
	* @brief  Configuration de l'USART1
  * @note   baud rate = 9600 , 8 bits de données,1 bit de stop
	* @param  
  * @retval Aucun
  */
	
	void USART1_Conf() {
		
		USART1_Conf_io();
		// activation de la clock du périphérique du port A lié à APB1
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1); 	
	
	
		// initialisation de la structure de type LL_USART_InitTypeDef 
		LL_USART_InitTypeDef My_LL_USART1; 	
		 
		
		
		My_LL_USART1.BaudRate = 9600;                               // on met 9600 en baud rate
		My_LL_USART1.Parity = LL_USART_PARITY_NONE;                  // pas de bit de parité
		My_LL_USART1.DataWidth = LL_USART_DATAWIDTH_8B;              // 8 bit de données
		My_LL_USART1.StopBits = LL_USART_STOPBITS_1;                 // 1 bit de stop
		My_LL_USART1.TransferDirection = LL_USART_DIRECTION_NONE;      // TX est à 0 tant qu'il n'y a pas de transmission
		My_LL_USART1.HardwareFlowControl = LL_USART_HWCONTROL_NONE ; // pas de contrôle de flux
		
		LL_USART_Init(USART1,&My_LL_USART1);
		
			
		// activation USART1
	  LL_USART_Enable(USART1);
		
		// Half duplex
		LL_USART_EnableHalfDuplex(USART1);
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
	while(LL_USART_IsActiveFlag_TC(USART1)==0) {}   	// Attente de la fin de transmission	
		
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_11);	  // on passe PA11 à 0 : trasmission terminée
	
	}
