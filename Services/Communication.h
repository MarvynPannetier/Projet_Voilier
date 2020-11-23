//Communication.h


#include "Bordage_voile.h"
#include "UART.h"

void config_batterie(void);

/**
	* @brief  Calcul information bordage en cours
  * @note   vaut 0% si voiles relachées et 100% si voiles tendues au maximum
	* @param  
	* @retval valeur en pourcentage de l'ouverture des voiles
  */

int Calcul_Etat_Voiles(void);


/**
	* @brief  Envoie l'état de la voile
  * @note   vaut 0% si voiles relachées et 100% si voiles tendues au maximum
	* @param  
	* @retval 
  */

void Envoi_Etat_Voiles(void);




void gestion_batterie(void);
