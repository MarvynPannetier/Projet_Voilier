#include "ADC.h"
#include "GPIO.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"

void configure_adc1_single(int v) {
		//config du port de l'acceleromètre branché sur ...
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	  GPIO_input_conf(GPIOB, LL_GPIO_PIN_0  ,LL_GPIO_MODE_ANALOG); //PB0 en analog input
		//config de l'ADC
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; 	// validation horloge ADC1
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6; 		// passage de l'horloge ADC1 à 12MHz
    ADC1->CR2|= ADC_CR2_ADON; 						// démarrage ADC1
    ADC1->SQR1&= ADC_SQR1_L; 							// fixe le nombre de conversions à 1
    ADC1->SQR3|= v; 											// indique la voie à convertir
    ADC1->CR2 |= ADC_CR2_CAL; 						// debut de la calibration
    while ((ADC1->CR2 & ADC_CR2_CAL)); 		// attente de la fin de la calibration
}

void configure_adc2_single(int v) {
		//config du port de l'acceleromètre branché sur ...
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
     GPIO_input_conf(GPIOC, 2 ,LL_GPIO_MODE_ANALOG); //PC2 en analog input
		//config de l'ADC
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN; 	// validation horloge ADC1
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6; 		// passage de l'horloge ADC1 à 12MHz
    ADC2->CR2|= ADC_CR2_ADON; 						// démarrage ADC1
    ADC2->SQR1&= ADC_SQR1_L; 							// fixe le nombre de conversions à 1
    ADC2->SQR3|= v; 											// indique la voie à convertir
    ADC2->CR2 |= ADC_CR2_CAL; 						// debut de la calibration
    while ((ADC2->CR2 & ADC_CR2_CAL)); 		// attente de la fin de la calibration
}

int convert_single1(void){
    ADC1->CR2 |= ADC_CR2_ADON; 						// lancement de la conversion
    while(!(ADC1->SR & ADC_SR_EOC) ) {} 	// attente de la fin de conversion
    ADC1->SR &= ~ADC_SR_EOC; 							// validation de la conversion
    return ADC1->DR & ~((0x0F) << 12); 		// retour de la conversion
}

int convert_single2(void){
    ADC2->CR2 |= ADC_CR2_ADON; 						// lancement de la conversion
    while(!(ADC2->SR & ADC_SR_EOC) ) {} 	// attente de la fin de conversion
    ADC2->SR &= ~ADC_SR_EOC; 							// validation de la conversion
    return ADC2->DR & ~((0x0F) << 12); 		// retour de la conversion
}

//void configure_perif(void) {
//	//configure les périphériques
//	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
//	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
//  GPIOB->CRL &= ~((0x1 << 0) | (0x1 << 1) | (0x1 << 2) | (0x1 << 3)); // PB.0 analog input
//	GPIOA->CRL &= ~(0xF << 24); 																				// PA.6 alternate push-pull
//  GPIOA->CRL |= (0xA << 24); 																					// PA.6 alternate push-pull
//}


