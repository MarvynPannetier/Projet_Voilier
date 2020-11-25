
#include "stm32f1xx_ll_rcc.h" // utile dans la fonction SystemClock_Config
#include "stm32f1xx_ll_utils.h"   // utile dans la fonction SystemClock_Config
#include "stm32f1xx_ll_system.h" // utile dans la fonction SystemClock_Config
#include "stm32f1xx_ll_tim.h" 
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_bus.h" 


#include "orientation_plateau.h"
#include "envoi_donnees.h"
#include "Bordage_voile.h"
#include "Communication.h"
#include "Securite.h"


void  SystemClock_Config(void);

//Déclaration des variables de l'ordonnanceur

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
	
//Déclaration des variables de l'ordonnanceur	
	int compteur_chavirement = 0 ;
	int compteur_batterie = 0 ;
	int compteur_voile = 0;
	int compteur_emetteur = 0;
	int compteur_plateau = 0;

/*J'ai réorganisé chaque couche : 
-dans chacunes aucun fichier n'est dépendant de l'autre, ils sont tous en parallèles
-j'ai donc laissé dans la couche que les fonctions essentielles 
-dans la couche services, j'ai recombiné les fonctions de la couche driver pour pouvoir configurer chacunes des parties
-dans la couche services, il y a aussi nos fonctions de traitement qui sont appelées dans la boucle while du main ou dans les interuption SYSTICK
-dans le main, j'ai commencé par appeler toutes les fonctions de configuration. Le but étant qu'on ne reconfigure pas à chaque fois qu'on utilise un périph 
-Si une pin change le jour du test il faut donc juste modifier les arguments de ces fonctions au début du main
-j'ai activé la clock des GPIO en dehors des fonctions de conf pour éviter de l'activer dans chaque fonction comme tout le monde s'en sert
-enfin j'ai rajouté notre partie à Thomas et moi dans le main, je l'ai mis dans le while et non dans le systick pour etre à l'écoute de la télécommande 
-Idéalement il ne reste plus qu'à tester tout ça 
-ATTENTION : ne pas push de version test, git va vouloir recombiner et ça va demander du travail à la main, pour enlever les lignes de test par exemple
-Push uniquement si la version actuelle à des problèmes(ce qui est quand même probable), pour la modifier, mais sur git on ne met que des versions améliorées de celle-ci et qui fonctionnent maintenant
-j'ai aussi fait le tour pas mal de fois de chaque fichier pour enlever les includes inutiles par exemple  
*/

int main(void)
{

	//configuration du systick pour interruption toutes les 1 ms
	SystemClock_Config();
	SysTick->CTRL |= (1<<1); //autorise interruption
	
	// activation de la clock du périphérique du port A lié à APB2
	// activation de la clock du périphérique du port B lié à APB2
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
	
	// activation de la clock du périphérique du port A lié à APB1
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1); 
	
	// configuration des fonctions de service
	config_girouette(); 
	config_orientation();
	config_chavirement(8);
	config_batterie(12);
	config_envoi() ;
	

  while (1)
  {
		
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
	compteur_chavirement ++ ; 
	if (compteur_chavirement==100) {
		compteur_chavirement=0;
		gestion_chavirement();
	}
	
/* gestion du bordage de la voile , tous les 20 ms*/
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
	
/* gestion de la batterie, tous les secondes*/
	
	compteur_batterie ++ ;
	if (compteur_batterie==1000) {
		compteur_batterie=0;
		gestion_batterie();
	}

//gestion rotaion plateau toute les 100ms 	
	
	compteur_plateau ++ ;
	if (compteur_plateau==100) {
		compteur_plateau=0;
		Rotation_plateau();
	}
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
