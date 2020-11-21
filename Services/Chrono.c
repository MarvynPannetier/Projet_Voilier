// A COMPLETER

/*
Service permettant de chornom�trer jusqu'� 59mn 59s 99 1/100
Utilise un timer au choix (TIMER1 � TIMER4).
Utilise la lib MyTimers.h /.c
*/



#include "Chrono.h"
#include "MyTimer.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_bus.h" // Pour l'activation des horloges



// variable priv�e de type Time qui m�morise la dur�e mesur�e
static Time Chrono_Time; // rem : static rend la visibilit� de la variable Chrono_Time limit�e � ce fichier 

// variable priv�e qui m�morise pour le module le timer utilis� par le module
static TIM_TypeDef * Chrono_Timer=TIM1; // init par d�faut au cas o� l'utilisateur ne lance pas Chrono_Conf avant toute autre fct.

// d�claration callback appel� toute les 10ms
void Chrono_Task_10ms(void);

/**
	* @brief  Configure le chronom�tre. 
  * @note   A lancer avant toute autre fonction.
	* @param  Timer : indique le timer � utiliser par le chronom�tre, TIM1, TIM2, TIM3 ou TIM4
  * @retval None
  */
void Chrono_Conf(TIM_TypeDef * Timer)
{
	
	// Configuration des entr�es et des sorties
	Chrono_Conf_io();
	
	// Reset Time
	Chrono_Time.Hund=0;
	Chrono_Time.Sec=0;
	Chrono_Time.Min=0;
	
	// Fixation du Timer
	Chrono_Timer=Timer;

	// R�glage Timer pour un d�bordement � 10ms
	MyTimer_Conf(Chrono_Timer,999, 719);
	
	// R�glage interruption du Timer avec callback : Chrono_Task_10ms()
	MyTimer_IT_Conf(Chrono_Timer, Chrono_Task_10ms,3);
	
	// Validation IT
	MyTimer_IT_Enable(Chrono_Timer);
	
	
}


/**
	* @brief  D�marre le chronom�tre. 
  * @note   si la dur�e d�passe 59mn 59sec 99 Hund, elle est remise � z�ro et repart
	* @param  Aucun
  * @retval Aucun
  */
void Chrono_Start(void)
{
	MyTimer_Start(Chrono_Timer);
}


/**
	* @brief  Arr�te le chronom�tre. 
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void Chrono_Stop(void)
{
	MyTimer_Stop(Chrono_Timer);
}


/**
	* @brief  Remet le chronom�tre � 0 
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void Chrono_Reset(void)
{
  // Arr�t Chrono
	MyTimer_Stop(Chrono_Timer);

	// Reset Time
	Chrono_Time.Hund=0;
	Chrono_Time.Sec=0;
	Chrono_Time.Min=0;
}


/**
	* @brief  Renvoie l'adresse de la variable Time priv�e g�r�e dans le module Chrono.c
  * @note   
	* @param  Aucun
  * @retval adresse de la variable Time
  */
Time * Chrono_Read(void)
{
	return &Chrono_Time;
}




/**
	* @brief  incr�mente la variable priv�e Chrono_Time modulo 60mn 
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void Chrono_Task_10ms(void)
{ 
	Chrono_Time.Hund++;
	if (Chrono_Time.Hund==100)
	{
		//LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_10);			// toutes les secondes, on bascule la valeur de la pin 10 de GPIOC -> on allume et on �teint la LED � une fr�quence de 1Hz
		Chrono_Time.Sec++;
		Chrono_Time.Hund=0;
	}
	if (Chrono_Time.Sec==60)
	{
		Chrono_Time.Min++;
		Chrono_Time.Sec=0;
	}
	if (Chrono_Time.Min==60)
	{
		Chrono_Time.Hund=0;
	}
	
}


/**
	* @brief  Configuration des 3 IO pour recevoir les 2 boutons poussoirs et la LED
  * @note   
	* @param  Aucun
  * @retval Aucun
  */

void Chrono_Conf_io(void) {
	
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC); // activation de la clock du p�riph�rique du port C li� � APB2
	
		//----------- initialisation de la structure de type LL_GPIO_InitTypeDef------------------------
	
		LL_GPIO_InitTypeDef My_LL_GPIOC_StartStop; // pour le bouton StartStop
		LL_GPIO_InitTypeDef My_LL_GPIOC_User; // pour le bouton User
		LL_GPIO_InitTypeDef My_LL_GPIOC_LED; // pour la LED
		
		
	
		
		//-----------configuration de chaque port sur le pin et dans le mode souhait� ------------------------
	
		// Configuration du start/stop en mode Floating Input --> Port C Pin 8 --> 0100
		My_LL_GPIOC_StartStop.Pin=LL_GPIO_PIN_8;
		My_LL_GPIOC_StartStop.Mode=LL_GPIO_MODE_FLOATING;
		My_LL_GPIOC_StartStop.Speed=LL_GPIO_SPEED_FREQ_MEDIUM;
		

		// Configuration du USER en mode Floating Input --> Port C Pin 13 --> 0100
		My_LL_GPIOC_User.Pin=LL_GPIO_PIN_13;
		My_LL_GPIOC_User.Mode=LL_GPIO_MODE_FLOATING;
		My_LL_GPIOC_User.Speed=LL_GPIO_SPEED_FREQ_MEDIUM;
		
		
		// Configuration de la LED PC10 en output PushPull --> Port C Pin 10 --> 0001 par exemple
		My_LL_GPIOC_LED.Pin=LL_GPIO_PIN_10;
		My_LL_GPIOC_LED.Mode=LL_GPIO_MODE_OUTPUT;
		My_LL_GPIOC_LED.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
		My_LL_GPIOC_LED.Speed=LL_GPIO_SPEED_FREQ_MEDIUM;
		
		
		
		//----------- affiliation des structures au GPIO correspondant ------------------------
	
		LL_GPIO_Init(GPIOC, &My_LL_GPIOC_StartStop); // bouton Start/Stop = Port C
		LL_GPIO_Init(GPIOC, &My_LL_GPIOC_LED); // LED = Port C
		LL_GPIO_Init(GPIOC, &My_LL_GPIOC_User); // bouton USER = Port C


}


/**
	* @brief  Lecture des diff�rentes entr�es et actions sur les sorties
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void Chrono_Background(void) {
	
	// en simulation, la LED clignote car le PIN 8 reste toujours � 1. Il faudrait int�grer une variable globale qui g�re l'�tat du bouton.
	// on ne change l'�tat de la LED que si le bouton passe de 0 � 1 et pas quand on reste appuy� (donc quand on reste � 1)
	
	
	if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_8)){				// si on presse le bouton start -> le bit de rang 8 du registre IDR passe � 1
		if (LL_GPIO_IsOutputPinSet(GPIOC, LL_GPIO_PIN_10)) {	// si elle la LED est d�j� allum�e -> le bit de rang 10 du registre IDR passe � 1
			 LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_10);			// alors on l'�teint
		}
		else {
			LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_10);				// sinon (si elle �tait �teinte) on l'allume
		}
		
	}

		
	if (LL_GPIO_IsInputPinSet(GPIOC,LL_GPIO_PIN_13)) {			// si on presse le bouton USER -> le bit de rang 13 du registre IDR passe � 1
		Chrono_Reset();																				// on reset le chrono
	}
	
	
}


