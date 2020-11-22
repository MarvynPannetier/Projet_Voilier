//Securite.c;
#include "ADC.h"
#include "Securite.h" 

#define valeur_critique_chavirement 1620

//proc�dure qui se d�clenche si on d�tecte un chavirement, et s'interrompt une fois le chavirement emp�ch�

void gestion_chavirement(void) {
	
	while(convert_single1() < valeur_critique_chavirement){ 	//on mesure l'angle de roulis avec convert_single()
	envoi_donnee('c'); 																			//on envoi l'info qu'on est en train de chavirer
	PWM_Output_Pulse(TIM4,10); 															//on borde les voiles � 90� pour emp�cher le chavirement
	}
}





