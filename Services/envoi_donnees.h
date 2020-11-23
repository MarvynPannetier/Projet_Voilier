//envoi_donnees

/**
	* @brief  Configuration des IO en Output et configure USART
  * @note   PA11 en alternate Push-Pull et PA9 en Push-Pull
	* @param  
  * @retval Aucun
  */
	
   void config_envoi(void) ;
	
	
	
	/**
	* @brief  envoi de la donnée par l'USART1 et gestion de TX
  * @note   baud rate = 9600 , 8 bits de données,1 bit de stop
	* @param  
  * @retval Aucun
  */
	
	void envoi_donnee(char data);

