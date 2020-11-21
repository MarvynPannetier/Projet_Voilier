//Bordage_voile.h


#include "GPIO.h"
#include "ENCODER.h"
#include "PWM.h"
#include "stm32f103xb.h" 


/**
	* @brief  Reset et d�marrage du Timer 3 
  * @note   Fonction appel�e quand l'index est d�tect� --> au d�clenchement de l'interruption correspondante
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
  * @note   Fonction � appeler en argument de la fonction PWM_Out_Pulse
	* @param  int Alpha : valeur de l'angle mesur� par la girouette = direction du vent
	* @retval int Pulse : valeur du duty cycle de la PWM du servo moteur
  */


int Calcul_duty_cycle(int alpha);

/**
	* @brief  Actualisation de la valeur de l'angle des voiles en fonction de la direction du vent
  * @note   Fonction � appeler dans le While(1) 
	* @param  
	* @retval 
  */

void Asservissement_voile(void);
