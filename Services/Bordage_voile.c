//Bordage_voile;


#include "Bordage_voile.h"
#include "stm32f1xx_ll_tim.h" 
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_bus.h" 
#include "stm32f1xx_ll_exti.h"

	
	
void Demarrage_Timer() {
		
		// Dès que l'on détecte l'index, on remet le Timer3 à 0
		MyTimer_Reset(TIM3);
		
		// Puis on commence à compter pour calculer la valeur de l'angle
		MyTimer_Start(TIM3);

	}
	
	

/**
	* @brief  Configuration de la girouette et de la PWM en Output pour le servo-moteur
  * @note   A lancer avant toute autre fonction.
	* @param  
  * @retval None
  */
	
	
void Girouette_Conf() {
	
	// Configuration du PWM Output
	PWM_OUT_Conf(TIM4,LL_TIM_CHANNEL_CH3,5);
	
	// configuration du timer en mode encoder associé aux voies A et B de la girouette
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA)
	
	// 1- Configurer GPIO en floating input 
	GPIO_input_conf(GPIOA, LL_GPIO_PIN_6, LL_GPIO_MODE_FLOATING, LL_GPIO_SPEED_FREQ_MEDIUM);
	GPIO_input_conf(GPIOA, LL_GPIO_PIN_7, LL_GPIO_MODE_FLOATING, LL_GPIO_SPEED_FREQ_MEDIUM);
	
	// 2- Activation de la clock du timer 3
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
	
	// 3- Configurer les valeurs ARR (=360) et PSC(=0) du Timer --> utilisation de la fonction My_Timer_Conf
	MyTimer_Conf(TIM3,359,0);
	
	Encoder_Conf_Timer();
	
	// configuration de l'entrée associé à l'index 
	GPIO_input_conf(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_FLOATING, LL_GPIO_SPEED_FREQ_MEDIUM);
	
	
  //configuration de l'interruption de index
	
	
	Index_Conf(Demarrage_Timer);
	
	
	
}


	
}





int Calcul_duty_cycle(int alpha) {

	int pulse = 0; 					// valeur du duty cycle
	
	if (alpha <= 180) {
		pulse = 1/18 * (alpha/2) + 5;
	}
	
	else {
		pulse = 1/18 * (360-alpha/2) + 5;
	}
	
	return pulse;
	
}



/**
	* @brief  Actualisation de la valeur de l'angle des voiles en fonction de la direction du vent
  * @note   Fonction à appeler dans le While(1) 
	* @param  
	* @retval 
  */

void Asservissement_voile() {
	
	// Actualisation de la valeur du pulse = duty cycle
	PWM_Output_Pulse(TIM4, Calcul_duty_cycle(TIM3->CNT));
	
}



