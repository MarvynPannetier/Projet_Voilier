//Securite.c;
#include "Securite.h" 
#include "GPIO.h"
#include "stm32f1xx_ll_gpio.h"
#include "envoi_donnees.h"

#define valeur_critique_chavirement 1620

//procédure qui se déclenche si on détecte un chavirement, et s'interrompt une fois le chavirement empêché

void gestion_chavirement(int res) {
	
	while(res < valeur_critique_chavirement){ 		//on mesure l'angle de roulis avec convert_single()
	
	envoi_donnee('c'); 																			//on envoi l'info qu'on est en train de chavirer
	PWM_Output_Pulse(TIM4,10); 															//on borde les voiles à 90° pour empêcher le chavirement
	}
}


void conf_adc_chavirement(int v)
{
  GPIO_input_conf(GPIOB, LL_GPIO_PIN_0  ,LL_GPIO_MODE_ANALOG,LL_GPIO_SPEED_FREQ_LOW); //PB0 en analog input 
	configure_adc1_single(v);
}

