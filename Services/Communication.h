//Communication.h

//-> include UART
//-> include PWM

#include "Bordage_voile.h"

/**
	* @brief  Calcul information bordage en cours
  * @note   vaut 0% si voiles relachées et 100% si voiles tendues au maximum
	* @param  
	* @retval valeur en pourcentage de l'ouverture des voiles
  */

int Calcul_Etat_Voile(void);
