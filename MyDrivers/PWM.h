#include "stm32f103xb.h" 
#include "MyTimer.h"

/**
	* @brief  Configuration des IO en Output alternate Push-Pull
  * @note   Pour les pins PA1 = TIM2_CH2 pour le moteur CC ou PB8 = TIM4_CH3 pour le servo moteur
	* @param  TIM_TypeDef Timer : indique le timer à configurer TIM2 ou TIM4
  * @retval Aucun
  */

void PWM_OUT_Conf_io(TIM_TypeDef * Timer);


/**
	* @brief  Configuration du timer en mode PWM
  * @note   Pour les pins PA1 = TIM2_CH2 pour le moteur CC ou PB8 = TIM4_CH3 pour le servo moteur
	* @param  TIM_TypeDef Timer : indique le timer à configurer TIM2 ou TIM4
						int pulse : valeur du rapport cyclique
  * @retval Aucun
  */


void PWM_Output_Conf_TIM(TIM_TypeDef * Timer);

/**
	* @brief  Configuration de la valeur du duty cycle
  * @note   Pour les pins PA1 = TIM2_CH2 pour le moteur CC ou PB8 = TIM4_CH3 pour le servo moteur
	* @param  TIM_TypeDef Timer : indique le timer à configurer TIM2 ou TIM4
						int pulse : valeur du rapport cyclique
  * @retval Aucun
  */

void PWM_Output_Pulse(TIM_TypeDef * Timer, int pulse);



/**
	* @brief  Configuration de la PWM Output
  * @note   Pour les pins PA1 = TIM2_CH2 pour le moteur CC ou PB8 = TIM4_CH3 pour le servo moteur
	* @param  TIM_TypeDef Timer : indique le timer à configurer TIM2 ou TIM4
  * @retval Aucun
  */

void PWM_OUT_Conf(TIM_TypeDef * Timer);
