
//Communication.c;
#include "Communication.h"
#include "stm32f1xx_ll_gpio.h"
#include "ADC.h"
#include "UART.h"

/**
	* @brief  Calcul information bordage en cours
  * @note   vaut 0% si voiles relachées et 100% si voiles tendues au maximum
	* @param  
	* @retval valeur en pourcentage de l'ouverture des voiles
  */

int Calcul_Etat_Voiles() {
	return 20*(Calcul_duty_cycle(TIM3->CNT)-5); // valeur pourcentage = 100/5 * (duty_cycle_PWM - 5)
}



/**
	* @brief  Envoie l'état de la voile
  * @note   vaut 0% si voiles relachées et 100% si voiles tendues au maximum
	* @param  
	* @retval 
  */

void Envoi_Etat_Voiles() {
	char data = (char) Calcul_Etat_Voiles();    // On récupère la valeur qu'on transforme en caractère
	envoi_donnee('data');

}

