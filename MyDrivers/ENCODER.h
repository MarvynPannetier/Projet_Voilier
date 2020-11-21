//ENCODER.h

#include "MyTimer.h"

#include "stm32f103xb.h" 

/**
	* @brief  Configuration des IO PA6 et PA7 en floating input
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
	
void Encoder_Conf_io(void) ;



/**
	* @brief  Initialisation du Timer en mode ENCODER
  * @note   
	* @param  Aucun
  * @retval Aucun
  */

void Encoder_Conf_Timer(void);



/**
	* @brief Configuration du Timer 3 en mode ENCODER
  * @note   
	* @param  Aucun
  * @retval Aucun
  */

void Encoder_Conf(void);

