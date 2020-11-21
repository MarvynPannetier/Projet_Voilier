//Bordage_voile;


#include "Bordage_voile.h"






/**
	* @brief  Reset et démarrage du Timer 3 
  * @note   Fonction appelée quand l'index est détecté --> au déclenchement de l'interruption correspondante
	* @param  None
  * @retval None
  */
	
	
	
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
	PWM_OUT_Conf(TIM4);
	
	// configuration du timer en mode encoder associé aux voies A et B de la girouette
	Encoder_Conf();
	
	// configuration de l'entrée associé à l'index 
	Index_Conf(Demarrage_Timer);
	
	
	
}



/**
	* @brief  On exprime pulse en fonction de la valeur de l'angle de la girouette 
  * @note   Fonction à appeler en argument de la fonction PWM_Out_Pulse
	* @param  int Alpha : valeur de l'angle mesuré par la girouette = direction du vent
	* @retval int Pulse : valeur du duty cycle de la PWM du servo moteur
  */


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

