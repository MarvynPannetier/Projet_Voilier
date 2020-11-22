#include "PWM.h"
#include "stm32f1xx_ll_bus.h" // Pour l'activation des horloges
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_tim.h" 


// étapes configurations PWM OUTPUT 

// 1- Configuration TIMER avec les bonnes valeurs ARR-PSC pour avoir la bonne fréquence de la PWM (procédure déjà existante dans My_Timer)
// 2- Configuation des IO --> moteur CC = PA1 (TIM2_CH2) et servo moteur = PB8 (TIM4_CH3) --> en alternate push pull
// 3- Configurer les pins en mode PWM 
// 4- Lancer le timer
// 5- Régler la durée de l'impulsion



/**
	* @brief  Configuration des IO en Output alternate Push-Pull
  * @note   Pour les pins PA1 = TIM2_CH2 pour le moteur CC ou PB8 = TIM4_CH3 pour le servo moteur
	* @param  TIM_TypeDef Timer : indique le timer à configurer TIM2 ou TIM4
  * @retval Aucun
  */

void PWM_OUT_Conf_io(TIM_TypeDef * Timer) {
	
	if (Timer==TIM2) {	// moteur CC
		
		// activation de la clock du périphérique du port A lié à APB1
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA); 	
		
		// initialisation de la structure de type LL_GPIO_InitTypeDef 
		LL_GPIO_InitTypeDef My_LL_GPIOA; 											
		
		// Configuration en output Alternate PushPull --> Port A Pin 1 --> fréquence 20kHz
		My_LL_GPIOA.Pin=LL_GPIO_PIN_1;
		My_LL_GPIOA.Mode = LL_GPIO_MODE_ALTERNATE;
		My_LL_GPIOA.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
		My_LL_GPIOA.Speed=LL_GPIO_SPEED_FREQ_LOW;
		
		LL_GPIO_Init(GPIOA, &My_LL_GPIOA);
		
	}
	
	
	if (Timer==TIM4) {	 // servo moteur 
		
		// activation de la clock du périphérique du port B lié à APB1
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB); 	
		
		// initialisation de la structure de type LL_GPIO_InitTypeDef
		LL_GPIO_InitTypeDef My_LL_GPIOB; 											 
		
		// Configuration en output Alternate PushPull --> Port B Pin 8 --> fréquence 50Hz < 1MHz
		My_LL_GPIOB.Pin = LL_GPIO_PIN_8;
		My_LL_GPIOB.Mode = LL_GPIO_MODE_ALTERNATE;
		My_LL_GPIOB.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
		My_LL_GPIOB.Speed = LL_GPIO_SPEED_FREQ_LOW;

		
		LL_GPIO_Init(GPIOB, &My_LL_GPIOB);
	}
	
	
}



/**
	* @brief  Configuration du timer en mode PWM
  * @note   Pour les pins PA1 = TIM2_CH2 pour le moteur CC ou PB8 = TIM4_CH3 pour le servo moteur
	* @param  TIM_TypeDef Timer : indique le timer à configurer TIM2 ou TIM4
						int pulse : valeur du rapport cyclique
  * @retval Aucun
  */


void PWM_Output_Conf_TIM(TIM_TypeDef *Timer, uint32_t Channel) {
		
		LL_TIM_CC_EnableChannel(Timer,Channel);
		LL_TIM_OC_SetMode(Timer,Channel,LL_TIM_OCMODE_PWM1);
	 	
}


/**
	* @brief  Configuration de la valeur du duty cycle
  * @note   Pour les pins PA1 = TIM2_CH2 pour le moteur CC ou PB8 = TIM4_CH3 pour le servo moteur
	* @param  TIM_TypeDef Timer : indique le timer à configurer TIM2 ou TIM4
						int pulse : valeur du rapport cyclique
  * @retval Aucun
  */


void PWM_Output_Pulse(TIM_TypeDef * Timer, int pulse) {
	
	if (Timer == TIM2) {
		LL_TIM_OC_SetCompareCH2(Timer,Timer->ARR*pulse/100);
	}
	
	if (Timer == TIM4) {
		LL_TIM_OC_SetCompareCH3(Timer,Timer->ARR*pulse/100);
	}
	
}


/**
	* @brief  Configuration de la PWM Output
  * @note   Pour les pins PA1 = TIM2_CH2 pour le moteur CC ou PB8 = TIM4_CH3 pour le servo moteur
	* @param  TIM_TypeDef Timer : indique le timer à configurer TIM2 ou TIM4
						int pulse : valeur du rapport cyclique
  * @retval Aucun
  */
	
	
void PWM_OUT_Conf(TIM_TypeDef * Timer, uint32_t Channel,int pulse)
	{	
	// Configuration de l'IO en Output PushPull
//	PWM_OUT_Conf_io(Timer);
	
	// Configuration du timer avec une periode de 20ms/fréquence de 20khz
//	MyTimer_Conf(Timer, 3599, 0);
	
	// Configuration du Timer en mode PWM
	PWM_Output_Conf_TIM(Timer, Channel);
	
	// Configuration du rapport cyclique
	PWM_Output_Pulse(Timer, pulse);
	
	// Active le timer
	MyTimer_Start(Timer);
	
}



