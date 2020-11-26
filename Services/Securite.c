//Securite.c;
#include "Securite.h" 
#include "GPIO.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_tim.h"
#include "UART.h"

#define valeur_critique_chavirement 0x8D0

//procédure qui se déclenche si on détecte un chavirement, et s'interrompt une fois le chavirement empêché

void gestion_chavirement() {
	
	while(convert_single1() < valeur_critique_chavirement){ 		//on mesure l'angle de roulis avec convert_single()
	envoi_donnee('c');
envoi_donnee('h');
		envoi_donnee('a');
		envoi_donnee('v');
		envoi_donnee('i');
		envoi_donnee('r');
		envoi_donnee('e');
		envoi_donnee('m');
		envoi_donnee('e');
		envoi_donnee('n');
		envoi_donnee('t');
		envoi_donnee(' ');
    envoi_donnee('\n');
		//envoi_donnee(0x0D);
	
		


		//on envoi l'info qu'on est en train de chavirer
	PWM_Output_Pulse(TIM4,5); 															//on borde les voiles à 90° pour empêcher le chavirement
	}
	
	
}


void config_chavirement(int v){
  GPIO_input_conf(GPIOC, LL_GPIO_PIN_1  ,LL_GPIO_MODE_ANALOG); //PB0 en analog input 
	configure_adc1_single(v);
}

//faire marcher pwm moteur cc
