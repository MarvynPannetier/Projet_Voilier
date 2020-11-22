/**
  ******************************************************************************
  * @file    Templates_LL/Src/main.c
  * @author  MCD Application Team
  * @brief   Main program body through the LL API
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
#include "stm32f1xx_ll_rcc.h" // utile dans la fonction SystemClock_Config
#include "stm32f1xx_ll_utils.h"   // utile dans la fonction SystemClock_Config
#include "stm32f1xx_ll_system.h" // utile dans la fonction SystemClock_Config


#include "ADC.h"
#include "PWM.h"
#include "UART.h"

#include "Bordage_voile.h"
#include "Communication.h"
#include "Securite.h"


void  SystemClock_Config(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
	
	int res = 2000 ; 					//moitié de la pleine échelle de l'ADC
	int compteur_ADC = 0 ;
	int compteur_voile = 0;
	int compteur_emetteur = 0;
	

int main(void)
{
  /* Configure the system clock to 72 MHz */
	SystemClock_Config();
	SysTick->CTRL |= (1<<1); //autorise interruption


	/* Configure l'adc sur la voie en argument */
	//configure_adc1_single(8); 	//brancher le potentiomètre sur PB0
	//PWM_OUT_Conf(TIM2); 				//PWM en sortie sur PA1 si TIM2, sur PB8 si TIM4
	//PWM_Output_Pulse(TIM2,50);
 
	
	USART1_Conf();
	
	envoi_donnee('a');
	
	
  while (1)
  {
		//tâche de fond : transmission USART
  }
}







/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 72000000
  *            HCLK(Hz)                       = 72000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            PLLMUL                         = 9
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  /* Set FLASH latency */
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);

  /* Enable HSE oscillator */
	// ********* Commenter la ligne ci-dessous pour MCBSTM32 *****************
	// ********* Conserver la ligne si Nucléo*********************************
  LL_RCC_HSE_EnableBypass();
  LL_RCC_HSE_Enable();
  while(LL_RCC_HSE_IsReady() != 1)
  {
  };

  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_1, LL_RCC_PLL_MUL_9);

  LL_RCC_PLL_Enable();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  };

  /* Sysclk activation on the main PLL */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  };

  /* Set APB1 & APB2 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

  /* Set systick to 1ms in using frequency set to 72MHz */
  LL_Init1msTick(72000000); // utile lorsqu'on utilise la fonction LL_mDelay

  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(72000000);
}



/* ==============   INTERUPTION SYSTICK = ORDONANCEUR          ============== */

void SysTick_Handler(void)  {   //le systick déborde toutes les 1ms                         
	
/* gestion du chavirement, tous les 100ms*/
	compteur_ADC ++ ;
	if (compteur_ADC==100) {
		compteur_ADC=0;
		gestion_chavirement();
	}
	
/* gestion du bordage de la voile , tous les 200 ms*/

	compteur_voile ++ ;
	if (compteur_voile==200) {
		compteur_voile=0;
		Asservissement_voile();
	}
	/* gestion de l'emetteur RF , tous les 3 s*/
	compteur_emetteur ++ ;
	if (compteur_emetteur==3000) {
		compteur_emetteur=0;
		Envoi_Etat_Voiles();
	}

	
/* gestion de la batterie, tous les ... ms*/
	
/* gestion de ... , tous les 100 ms*/
	
}



/* ==============   BOARD SPECIFIC CONFIGURATION CODE END      ============== */

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
