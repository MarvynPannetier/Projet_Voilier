//ENCODER;

#include "ENCODER.h"

#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_bus.h" // Pour l'activation des horloges

// Configuration mode ENCODER
// 1- Configurer GPIO en floating input 
// 2- Activation de la clock du timer 3
// 3- Configurer les valeurs ARR (=360) et PSC(=0) du Timer --> utilisation de la fonction My_Timer_Conf
// 4- Initialiser le timer en mode encoder --> on compte ou décompte en fonction du niveau des deux entrées



/**
	* @brief  Configuration des IO PA6 et PA7 en floating input
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
	
	
void Encoder_Conf_io() {
	
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA); // activation de la clock du périphérique du port A lié à APB2
	
	
	// initialisation de la structure de type LL_GPIO_InitTypeDef
	LL_GPIO_InitTypeDef My_LL_GPIOA_6;			
	LL_GPIO_InitTypeDef My_LL_GPIOA_7;
	
	// Configuration du Timer 3 - Chaine 1 en mode Floating Input --> Port A Pin 6 --> 0100
		My_LL_GPIOA_6.Pin=LL_GPIO_PIN_6;
		My_LL_GPIOA_6.Mode=LL_GPIO_MODE_FLOATING;
		My_LL_GPIOA_6.Speed=LL_GPIO_SPEED_FREQ_MEDIUM;
	
	// Configuration du Timer 3 - Chaine 1 en mode Floating Input --> Port A Pin 7 --> 0100
		My_LL_GPIOA_7.Pin=LL_GPIO_PIN_7;
		My_LL_GPIOA_7.Mode=LL_GPIO_MODE_FLOATING;
		My_LL_GPIOA_7.Speed=LL_GPIO_SPEED_FREQ_MEDIUM;
	
	//affiliation des structures au GPIO correspondant
		LL_GPIO_Init(GPIOA, &My_LL_GPIOA_6); 
		LL_GPIO_Init(GPIOA, &My_LL_GPIOA_7); 
	
	
}




/**
	* @brief  Initialisation du Timer en mode ENCODER
  * @note   
	* @param  Aucun
  * @retval Aucun
  */

void Encoder_Conf_Timer() {
	
	
	// initialisation de la structure de type LL_TIM_ENCODER_InitTypeDef
	LL_TIM_ENCODER_InitTypeDef My_LL_TIM_ENCODER;			
	

	// configuration du timer en mode encoder
	My_LL_TIM_ENCODER.EncoderMode=LL_TIM_ENCODERMODE_X4_TI12;
	
	// On configure le TI1
	My_LL_TIM_ENCODER.IC1ActiveInput=LL_TIM_ACTIVEINPUT_DIRECTTI;
	My_LL_TIM_ENCODER.IC1Polarity= LL_TIM_IC_POLARITY_RISING;
	My_LL_TIM_ENCODER.IC1Filter=LL_TIM_IC_FILTER_FDIV1;
	My_LL_TIM_ENCODER.IC1Prescaler=LL_TIM_ICPSC_DIV1;
	
	// On configure le TI2
	My_LL_TIM_ENCODER.IC2ActiveInput=LL_TIM_ACTIVEINPUT_DIRECTTI;
	My_LL_TIM_ENCODER.IC2Polarity= LL_TIM_IC_POLARITY_RISING;
	My_LL_TIM_ENCODER.IC2Filter=LL_TIM_IC_FILTER_FDIV1;
	My_LL_TIM_ENCODER.IC2Prescaler=LL_TIM_ICPSC_DIV1;
	
	//affiliation des structures au Timer correspondant
	LL_TIM_ENCODER_Init(TIM3,&My_LL_TIM_ENCODER);
}

/**
	* @brief Configuration du Timer 3 en mode ENCODER
  * @note   
	* @param  Aucun
  * @retval Aucun
  */

void Encoder_Conf() {
	
// 1- Configurer GPIO en floating input 
	Encoder_Conf_io();
	
// 2- Activation de la clock du timer 3
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
	
// 3- Configurer les valeurs ARR (=360) et PSC(=0) du Timer --> utilisation de la fonction My_Timer_Conf
	MyTimer_Conf(TIM3,359,0);
	
// 4- Initialiser le timer en mode encoder --> on compte ou décompte en fonction du niveau des deux entrées
	Encoder_Conf_Timer();
	
}

