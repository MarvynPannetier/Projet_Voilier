#include "ADC.h"
#include "stm32f1xx_ll_bus.h"

void configure_adc1_single(int v) {
		//config du port de l'acceleromètre branché sur ...
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    GPIOB->CRL &= ~((0x1 << 0) | (0x1 << 1) | (0x1 << 2) | (0x1 << 3)); //PB0 en analog input
		//config de l'ADC
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; 	// validation horloge ADC1
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6; 		// passage de l'horloge ADC1 à 12MHz
    ADC1->CR2|= ADC_CR2_ADON; 						// démarrage ADC1
    ADC1->SQR1&= ADC_SQR1_L; 							// fixe le nombre de conversions à 1
    ADC1->SQR3|= v; 											// indique la voie à convertir
    ADC1->CR2 |= ADC_CR2_CAL; 						// debut de la calibration
    while ((ADC1->CR2 & ADC_CR2_CAL)); 		// attente de la fin de la calibration
}

int convert_single(void){
    ADC1->CR2 |= ADC_CR2_ADON; 						// lancement de la conversion
    while(!(ADC1->SR & ADC_SR_EOC) ) {} 	// attente de la fin de conversion
    ADC1->SR &= ~ADC_SR_EOC; 							// validation de la conversion
    return ADC1->DR & ~((0x0F) << 12); 		// retour de la conversion
}

//void configure_perif(void) {
//	//configure les périphériques
//	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
//	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
//  GPIOB->CRL &= ~((0x1 << 0) | (0x1 << 1) | (0x1 << 2) | (0x1 << 3)); // PB.0 analog input
//	GPIOA->CRL &= ~(0xF << 24); 																				// PA.6 alternate push-pull
//  GPIOA->CRL |= (0xA << 24); 																					// PA.6 alternate push-pull
//}


