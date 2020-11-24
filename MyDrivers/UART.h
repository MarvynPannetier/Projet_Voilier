//UART.h


/**
	* @brief  Configuration de l'USART1
  * @note   baud rate = 9600 , 8 bits de donn�es,1 bit de stop
	* @param  
  * @retval Aucun
  */
	
	void USART1_Conf(void);

	/**
	* @brief  envoi de la donn�e par l'USART1 et gestion de TX
  * @note   baud rate = 9600 , 8 bits de donn�es,1 bit de stop
	* @param  
  * @retval Aucun
  */
	
	void envoi_donnee(char data);

