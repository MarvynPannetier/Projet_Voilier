//orientation_plateau;
#include "PWM.h"
#include "stm32f1xx_ll_tim.h"
#include "GPIO.h"
#include "stm32f1xx_ll_gpio.h"
#include "orientation_plateau.h"
#include "math.h"

void config_orientation(void)
{
	
// Configuration en input --> Port B Pin 6 
	
	//conf PB6 pour recevoir la pwm de la télécommande 
	
	GPIO_input_conf(GPIOB , LL_GPIO_PIN_7 , LL_GPIO_MODE_FLOATING);
	GPIO_input_conf(GPIOB , LL_GPIO_PIN_6 , LL_GPIO_MODE_FLOATING);
	//conf PA2 pour indiquer le sens de rotation
  GPIO_output_conf(GPIOA, LL_GPIO_PIN_2 , LL_GPIO_MODE_OUTPUT, LL_GPIO_SPEED_FREQ_LOW,LL_GPIO_OUTPUT_PUSHPULL) ;
	//conf PA1 pour envoyer la PWM au Moteur CC
	GPIO_output_conf(GPIOA, LL_GPIO_PIN_1 , LL_GPIO_MODE_ALTERNATE, LL_GPIO_SPEED_FREQ_LOW,LL_GPIO_OUTPUT_PUSHPULL) ;
	
	
	//Configuration TIM INPUT CAPTURE
	
  Conf_Input_Capture();
	
		// Configuration du timer avec une periode de 20ms/fréquence de 20khz
	MyTimer_Conf(TIM2, 3599, 0);
	
	// Configuration du Timer en mode PWM
	PWM_Output_Conf_TIM(TIM2,LL_TIM_CHANNEL_CH2);
	
	// Active le timer
	MyTimer_Start(TIM2);
	
}





void Rotation_plateau(){
	
	int period_hight ;	
	float vitesse ;
	
	
	
	//vérifier les données récupérer le jour du test 
	period_hight = (TIM4->CCR2) ;
	
	if ( period_hight > 0xB1 && period_hight < 0x10B)
	{
		LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_2) ;
	vitesse= ((-period_hight)+ 250);
	}
	else if (period_hight > 0x10D && period_hight < 0x153)
	{	
	 LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_2) ;
	vitesse = (period_hight - 300);  
	} 	
	else 
	{
		vitesse = 0 ;
	}
  
	//on envoie une PWM avec un duty cycle qui dépend de Timp pour que la vitesse varie 
	PWM_OUT_plateau(TIM2,vitesse); 
}

void PWM_OUT_plateau(TIM_TypeDef * Timer, int pulse)
	
 {
	// Configuration du rapport cyclique
	PWM_Output_Pulse(Timer, pulse);
		
}
