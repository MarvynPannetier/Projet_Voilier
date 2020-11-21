#include "stm32f103xb.h" 

//configure l'adc 1 pour single conversion de sa voie v
void configure_adc1_single(int v) ;

//procède à une conversion et retourne le résultat
int convert_single(void) ;

void set_pulse_percentage(TIM_TypeDef *TIMER, int pulse) ;
