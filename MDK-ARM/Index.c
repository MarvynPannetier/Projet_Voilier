//Index


#include "Bordage_voile.h"
#include "stm32f1xx_ll_tim.h" 
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_bus.h" 
#include "stm32f1xx_ll_exti.h"




/**
	* @brief  Configuration du Handler de l'interruption 
  * @note   
	* @param  
  * @retval Aucun
  */

void (*Ptr_ItFct_EXTI9_5)(void); //pointeur de fonction qui correspond à la fonction qui sera faite quand l'interruption sera déclenchée

void EXTI9_5_IRQHandler() {
	
	 LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_5); // rabaisser le flag d'IT
	(*Ptr_ItFct_EXTI9_5)(); // exécution de la fonction
	
}









/**
	* @brief  Configuration de la gestion de l'index de la girouette
  * @note   
	* @param  *void (*IT_function) (void) : nom (adresse) de la fonction à lancer sur interruption
						--> fonction à lancer dès que l'index est détecté
  * @retval Aucun
  */

void Index_Conf(void (*IT_function)(void)) {
	
	// Réglage interruption du Timer avec callback : 
	Index_IT_Conf(IT_function,1);
	
	// Validation IT
	Index_IT_enable();
	
}




/**
	* @brief  Configuration de l'interruption
  * @note   A ce stade, les interruptions ne sont pas validés (voir  Index_IT_Enable)
	* @param  *void (*IT_function) (void) : nom (adresse) de la fonction à lancer sur interruption
	*         int Prio : priorité associée à l'interruption
  * @retval None
  */

void Index_IT_Conf(void (*IT_function)(void), int Prio) {
	
	// affectation de la fonction
	Ptr_ItFct_EXTI9_5 = IT_function;
	
	// Blocage IT (il faudra la débloquer voir fct suivante)
	Index_IT_disable();
	
	// Configuration de l'interruption en détection de front montant
	Index_IT_rising_edge();
	
	// Configuration de la source de l'interruption --> détection sur la broche PA5
	Index_IT_Source();
	
	// validation du canal NVIC
	Index_IT_NVIC(Prio);
	
}








/**
	* @brief  Autorise l'interruption EXTI_5 
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
	
void Index_IT_enable() {
	LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_5);
}


/**
	* @brief  Interdit l'interruption EXTI_5 
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
	
void Index_IT_disable() {
	LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_5);
}



/**
	* @brief  Configuration de l'interruption au niveau du coeur --> gestion NVIC
  * @note   
	* @param  Prio = entier qui correspond à la priorité de l'interruption que l'on souhaite fixer
  * @retval Aucun
  */

void Index_IT_NVIC(int Prio) {
	// on autorise l'interruption
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	
	// on règle la priorité de l'interruption
	NVIC_SetPriority(EXTI9_5_IRQn,Prio);
}



/**
	* @brief  Configuration de l'interruption pour la détection de front montant
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
	

void Index_IT_rising_edge() {
	 LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_5);
}


















	
	
void Demarrage_Timer() {
		
		// Dès que l'on détecte l'index, on remet le Timer3 à 0
		MyTimer_Reset(TIM3);
		
		// Puis on commence à compter pour calculer la valeur de l'angle
		MyTimer_Start(TIM3);

	}
	
	


	










