void EXTI9_5_IRQHandler(void) ;
	
void Index_IT_Conf(void (*IT_function)(void), int Prio);
	
void Index_IT_Source(void);
	
void Index_IT_enable(void) ;
	
void Index_IT_disable(void);
	
void Index_IT_NVIC(int Prio);
	
void Index_IT_rising_edge(void);
