
//Communication.c;
#include "Communication.h"
#include "stm32f1xx_ll_bus.h" // Pour l'activation des horloges
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_tim.h" 
#include "stm32f1xx_ll_usart.h" 

/**
	* @brief  Calcul information bordage en cours
  * @note   vaut 0% si voiles relachées et 100% si voiles tendues au maximum
	* @param  
	* @retval valeur en pourcentage de l'ouverture des voiles
  */

int Calcul_Etat_Voile() {
	return 20*(Calcul_duty_cycle(TIM3->CNT)-5); // valeur pourcentage = 100/5 * (duty_cycle_PWM - 5)
}

