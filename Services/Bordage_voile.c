//Bordage_voile;


#include "Bordage_voile.h"
#include "stm32f1xx_ll_tim.h" 
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_bus.h" 

// on configure la PWM_output qui va être envoyé pour corriger la voile 
// on configure aussi le timer mode encoder pour pouvoir faire la comparaison entre A et B 
//enfin on configure l'index et l'interruption pour fixer l'angle de référence 
	
void Demarrage_Timer() {
		
		// Dès que l'on détecte l'index, on remet le Timer3 à 0
		MyTimer_Reset(TIM3);
		
		// Puis on commence à compter pour calculer la valeur de l'angle
		MyTimer_Start(TIM3);

	}
	
	

/**
	* @brief  Configuration de la girouette et de la PWM en Output pour le servo-moteur
  * @note   A lancer avant toute autre fonction.
	* @param  
  * @retval None
  */
	
	
void config_girouette() {

	// Configuration du PWM Output
	PWM_OUT_bordage();
	
	// configuration du timer en mode encoder associé aux voies A et B de la girouette
	Encoder_Conf();
	
	// configuration de l'entrée associé à l'index 
	Index_Conf(Demarrage_Timer);	
	
	
}


 
/**
	* @brief  On exprime pulse en fonction de la valeur de l'angle de la girouette 
  * @note   Fonction à appeler en argument de la fonction PWM_Out_Pulse
	* @param  int Alpha : valeur de l'angle mesuré par la girouette = direction du vent
	* @retval int Pulse : valeur du duty cycle de la PWM du servo moteur
  */

int Calcul_duty_cycle(float alpha) {

	float pulse = 0; 					// valeur du duty cycle
	
	if (alpha<45.0 || alpha>315.0) {
		pulse = 5;
	}
	if (alpha <= 180.0 && alpha >= 45.0) {
			
		pulse = (90 * alpha/135 - 30)/18 +5; // attention --> penser à modifier sous forme 1/18 * teta + 5
	}
	
	if (alpha > 180.0 && alpha <= 315.0) {
		
		pulse = (180.0 - (90 * alpha/135 - 30.0))/18+5.0;
	}
	 return pulse;
}



/**
	* @brief  Actualisation de la valeur de l'angle des voiles en fonction de la direction du vent
  * @note   Fonction à appeler dans le While(1) 
	* @param  
	* @retval 
  */

void Asservissement_voile() {
	
	// Actualisation de la valeur du pulse = duty cycle
	PWM_Output_Pulse(TIM4, Calcul_duty_cycle(TIM3->CNT));
	
}




/**
	* @brief  Configuration de la PWM Output
  * @note   configuration de PB8 = TIM4_CH3 pour le servo moteur
	* @param  Aucun
  * @retval Aucun
  */

void PWM_OUT_bordage()
	
 {
	
	// Configuration de l'IO bordage_voile en Output PushPull
	GPIO_output_conf(GPIOB, LL_GPIO_PIN_8, LL_GPIO_MODE_ALTERNATE, LL_GPIO_SPEED_FREQ_LOW, LL_GPIO_OUTPUT_PUSHPULL);
	
	// Configuration du timer 4 avec une periode de 20ms/fréquence de 20khz
	MyTimer_Conf(TIM4, 3599, 400);
	// Configuration du Timer en mode PWM
	PWM_Output_Conf_TIM(TIM4, LL_TIM_CHANNEL_CH3);
		
	// Active le timer
	MyTimer_Start(TIM4);
	
}
 

/**
	* @brief Configuration du Timer 3 en mode ENCODER
  * @note   
	* @param  Aucun
  * @retval Aucun
  */

void Encoder_Conf() {


  //1- Configurer GPIO ENCODER en floating input 
	GPIO_input_conf(GPIOA, LL_GPIO_PIN_6, LL_GPIO_MODE_FLOATING);
	GPIO_input_conf(GPIOA, LL_GPIO_PIN_7, LL_GPIO_MODE_FLOATING);
	
  // 2- Activation de la clock du timer 3
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
	
// 3- Configurer les valeurs ARR (=360) et PSC(=0) du Timer --> utilisation de la fonction My_Timer_Conf
	MyTimer_Conf(TIM3,360,0);
	
// 4- Initialiser le timer en mode encoder --> on compte ou décompte en fonction du niveau des deux entrées
	Encoder_Conf_Timer();
	
}


/**
	* @brief  Configuration de la gestion de l'index de la girouette
  * @note   
	* @param  *void (*IT_function) (void) : nom (adresse) de la fonction à lancer sur interruption
						--> fonction à lancer dès que l'index est détecté
  * @retval Aucun
  */

void Index_Conf(void (*IT_function)(void)) {
	
	// Configuration des entrées et des sorties
	GPIO_input_conf(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_FLOATING);
	
	// Réglage interruption du Timer avec callback : 
	Index_IT_Conf(IT_function,1);
	
	// Validation IT
	Index_IT_enable();
	
}


