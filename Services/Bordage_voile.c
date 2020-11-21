//Bordage_voile;


#include "Bordage_voile.h"






/**
	* @brief  Reset et d�marrage du Timer 3 
  * @note   Fonction appel�e quand l'index est d�tect� --> au d�clenchement de l'interruption correspondante
	* @param  None
  * @retval None
  */
	
	
	
void Demarrage_Timer() {
		
		// D�s que l'on d�tecte l'index, on remet le Timer3 � 0
		MyTimer_Reset(TIM3);
		
		// Puis on commence � compter pour calculer la valeur de l'angle
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
	
	// configuration du timer en mode encoder associ� aux voies A et B de la girouette
	Encoder_Conf();
	
	// configuration de l'entr�e associ� � l'index 
	Index_Conf(Demarrage_Timer);
	
	
	
}



/**
	* @brief  On exprime pulse en fonction de la valeur de l'angle de la girouette 
  * @note   Fonction � appeler en argument de la fonction PWM_Out_Pulse
	* @param  int Alpha : valeur de l'angle mesur� par la girouette = direction du vent
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
  * @note   Fonction � appeler dans le While(1) 
	* @param  
	* @retval 
  */

void Asservissement_voile() {
	
	// Actualisation de la valeur du pulse = duty cycle
	PWM_Output_Pulse(TIM4, Calcul_duty_cycle(TIM3->CNT));
	
}

