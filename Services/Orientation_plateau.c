//orientation_plateau;
#include "stm32f1xx_ll_gpio.h"
#include "ADC.h"
#include "PWM.h"
#include "UART.h"
#include "GPIO.h"
#include "stm32f103xb.h" 

void PWM_INPUT(){
	
	int period ;
	int duty ;
	int Timp ;	
	
	// Configuration en input --> Port B Pin 6 

	GPIO_input_conf(GPIOB , LL_GPIO_PIN_6 , LL_GPIO_MODE_INPUT);
  GPIO_output_conf(GPIOA, LL_GPIO_PIN_2 , LL_GPIO_MODE_ALTERNATE, LL_GPIO_SPEED_FREQ_LOW,LL_GPIO_OUTPUT_PUSHPULL) ;
	
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
	}
	else if (Timp > 7.8 && Timp < 10.3 )
	{	
	 LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_2) ;
	} 	

}