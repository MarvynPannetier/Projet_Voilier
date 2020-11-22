//orientation_plateau;
#include "stm32f1xx_ll_gpio.h"
#include "ADC.h"
#include "PWM.h"
#include "stm32f1xx_ll_tim.h"
#include "UART.h"
#include "GPIO.h"
#include "stm32f103xb.h" 
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_bus.h"

void PWM_INPUT(){
	
	int period ;
	int duty ;
	int Timp ;	
	int vitesse ;
	// Configuration en input --> Port B Pin 6 
  
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
	
	//conf PB6 pour recevoir la pwm de la télécommande 
	GPIO_input_conf(GPIOB , LL_GPIO_PIN_6 , LL_GPIO_MODE_INPUT);
	//conf PA2 pour indiquer le sens de rotation
  GPIO_output_conf(GPIOA, LL_GPIO_PIN_2 , LL_GPIO_MODE_ALTERNATE, LL_GPIO_SPEED_FREQ_LOW,LL_GPIO_OUTPUT_PUSHPULL) ;
	//conf PA1 pour envoyer la PWM au Moteur CC
	GPIO_output_conf(GPIOA, LL_GPIO_PIN_1 , LL_GPIO_MODE_ALTERNATE, LL_GPIO_SPEED_FREQ_LOW,LL_GPIO_OUTPUT_PUSHPULL) ;
	
	//Configuration du Timer de Base
	
	MyTimer_Conf(TIM4, 0xFFFF, 0);
	
	
	//Configuration TIM INPUT CAPTURE
  Conf_Input_Capture();
	
	
	//vérifier les données récupérer le jour du test 
	duty = TIM4->CCR2 ;
	period = TIM1->CCR1 ;
	Timp = (duty/period)*100 ;
	
	if ( Timp > 4.7 && Timp < 7.7)
	{
		LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_2) ;
	vitesse= (Timp + 40);
	}
	else if (Timp > 7.8 && Timp < 10.3 )
	{	
	 LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_2) ;
	vitesse = (Timp + 37.5);  
	} 	
  
	//on envoie une PWM avec un duty cycle qui dépend de Timp pour que la vitesse varie 
	PWM_OUT_Conf(TIM2,LL_TIM_CHANNEL_CH2,vitesse);
}


