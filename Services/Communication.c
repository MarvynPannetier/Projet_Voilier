
//Communication.c;
#include "Communication.h"
#include "stm32f1xx_ll_gpio.h"
#include "ADC.h"
#include "envoi_donnees.h"

float batterie_faible = 819 ; //batterie faible en dessous de 20%
//adc plage 0/3.3V 20% de 3.3V = 0.66V ; adc 12bit donc max 4096 et 0.2 x 4096 = 819 environ
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
	envoi_donnee(data);

}

void gestion_batterie(float res) {
	
	if (res < batterie_faible){ 		//on mesure le niveau de la batterie
	
	envoi_donnee('L'); 														//on envoi l'info que la batterie est faible
	envoi_donnee('o');
	envoi_donnee('w');
	envoi_donnee(' ');		
	envoi_donnee('B');
	envoi_donnee('a');
	envoi_donnee('t');	
	}
}

void conf_adc_batterie(int v)
{
  GPIO_input_conf(GPIOC, LL_GPIO_PIN_2 ,LL_GPIO_MODE_ANALOG,LL_GPIO_SPEED_FREQ_LOW); //PC2 en analog input
	configure_adc2_single(v);
}


