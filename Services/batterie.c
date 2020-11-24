#include "batterie.h"
#include "UART.h"
#include "stm32f1xx_ll_gpio.h"
#include "ADC.h"
#include "GPIO.h"


float batterie_faible = 819 ; //batterie faible en dessous de 20%
//adc plage 0/3.3V 20% de 3.3V = 0.66V ; adc 12bit donc max 4096 et 0.2 x 4096 = 819 environ

void gestion_batterie() {
	
	if (convert_single2() < batterie_faible){ 		//on mesure le niveau de la batterie
		envoi_donnee('b');
	}
}

void config_batterie(int v)
{
  GPIO_input_conf(GPIOC, LL_GPIO_PIN_2 ,LL_GPIO_MODE_ANALOG); //PC2 en analog input
	configure_adc2_single(v);
}


