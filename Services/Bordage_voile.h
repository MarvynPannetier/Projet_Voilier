//Bordage_voile.h


#include "GPIO.h"
#include "ENCODER.h"
#include "PWM.h"
#include "stm32f103xb.h" 


/**
	* @brief  Reset et démarrage du Timer 3 
  * @note   Fonction appelée quand l'index est détecté --> au déclenchement de l'interruption correspondante
	* @param  None
  * @retval None
  */
	
	
	
void Demarrage_Timer(void);
	
	
/**
	* @brief  Configuration de la girouette
  * @note   A lancer avant toute autre fonction.
	* @param  
  * @retval None
  */
	
	
void Girouette_Conf(void);


/**
	* @brief  On exprime pulse en fonction de la valeur de l'angle de la girouette 
  * @note   Fonction à appeler en argument de la fonction PWM_Out_Pulse
	* @param  int Alpha : valeur de l'angle mesuré par la girouette = direction du vent
	* @retval int Pulse : valeur du duty cycle de la PWM du servo moteur
  */


int Calcul_duty_cycle(int alpha);

/**
	* @brief  Actualisation de la valeur de l'angle des voiles en fonction de la direction du vent
  * @note   Fonction à appeler dans le While(1) 
	* @param  
	* @retval 
  */

void Asservissement_voile(void);


/**
	* @brief  Configuration de la PWM Output
  * @note   Pour les pins PA1 = TIM2_CH2 pour le moteur CC ou PB8 = TIM4_CH3 pour le servo moteur
	* @param  TIM_TypeDef Timer : indique le timer à configurer TIM2 ou TIM4
  * @retval Aucun
  */
	
void PWM_OUT_bordage(TIM_TypeDef * Timer, uint32_t Channel,int pulse);
