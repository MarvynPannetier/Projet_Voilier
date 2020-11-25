#include "PWM.h"
#include "stm32f1xx_ll_tim.h" 


// étapes configurations PWM OUTPUT 

// 1- Configuration TIMER avec les bonnes valeurs ARR-PSC pour avoir la bonne fréquence de la PWM (procédure déjà existante dans My_Timer)
// 2- Configuation des IO --> moteur CC = PA1 (TIM2_CH2) et servo moteur = PB8 (TIM4_CH3) --> en alternate push pull
// 3- Configurer les pins en mode PWM 
// 4- Lancer le timer
// 5- Régler la durée de l'impulsion
	
	

/**
	* @brief  Configuration du timer en mode PWM
  * @note   Pour les pins PA1 = TIM2_CH2 pour le moteur CC ou PB8 = TIM4_CH3 pour le servo moteur
	* @param  TIM_TypeDef Timer : indique le timer à configurer TIM2 ou TIM4
						int pulse : valeur du rapport cyclique
						uint32_t Channel : 
  * @retval Aucun
  */


void PWM_Output_Conf_TIM(TIM_TypeDef *Timer, uint32_t Channel) {
		
		LL_TIM_CC_EnableChannel(Timer, Channel);
		LL_TIM_OC_SetMode(Timer, Channel, LL_TIM_OCMODE_PWM1);
	 	
}


/**
	* @brief  Configuration de la valeur du duty cycle
  * @note   Pour les pins PA1 = TIM2_CH2 pour le moteur CC ou PB8 = TIM4_CH3 pour le servo moteur
	* @param  TIM_TypeDef Timer : indique le timer à configurer TIM2 ou TIM4
						int pulse : valeur du rapport cyclique
  * @retval Aucun
  */


void PWM_Output_Pulse(TIM_TypeDef * Timer, int pulse) {
	
	if (Timer == TIM2) {
		LL_TIM_OC_SetCompareCH2(Timer,Timer->ARR*pulse/100);
	}
	
	if (Timer == TIM4) {
		LL_TIM_OC_SetCompareCH3(Timer,Timer->ARR*pulse/100);
	}
	
}


	

