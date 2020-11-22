//GPIO.h

#include "stm32f103xb.h" 
#include "MyTimer.h"


// -------------------------- Gestion de l'index de la girouette -------------------------------// 



void GPIO_input_conf(GPIO_TypeDef *GPIOx, uint32_t pin, uint32_t mode) ;

void GPIO_output_conf(GPIO_TypeDef *GPIOx, uint32_t pin , uint32_t mode, uint32_t speed,uint32_t output_type) ;


/**
	* @brief  Configuration de l'IO PA5 en Floating input pour la gestion de l'index de la girouette 
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
	
	
void Index_Conf_io(void);



/**
	* @brief  Autorise l'interruption EXTI_5 
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
	
void Index_IT_enable(void);



/**
	* @brief  Interdit l'interruption EXTI_5 
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
	
void Index_IT_disable(void);



/**
	* @brief  Configuration de l'interruption pour la détection de front montant
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
	

void Index_IT_rising_edge(void);



/**
	* @brief  Configuration de la source de l'interruption = modification sur le PA5
  * @note   
	* @param  Aucun
  * @retval Aucun
  */


void Index_IT_Source(void);


/**
	* @brief  Configuration de l'interruption au niveau du coeur --> gestion NVIC
  * @note   
	* @param  Prio = entier qui correspond à la priorité de l'interruption que l'on souhaite fixer
  * @retval Aucun
  */


void Index_IT_NVIC(int Prio);





/**
	* @brief  Configuration de l'interruption
  * @note   A ce stade, les interruptions ne sont pas validés (voir  Index_IT_Enable)
	* @param  *void (*IT_function) (void) : nom (adresse) de la fonction à lancer sur interruption
	*         int Prio : priorité associée à l'interruption
  * @retval None
  */

void Index_IT_Conf(void (*IT_function)(void), int Prio);



/**
	* @brief  Configuration de la gestion de l'index de la girouette
  * @note   
	* @param  *void (*IT_function) (void) : nom (adresse) de la fonction à lancer sur interruption
						--> fonction à lancer dès que l'index est détecté
  * @retval Aucun
  */

void Index_Conf(void (*IT_function)(void));

