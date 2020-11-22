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



