/*
 * fsm_simple_buttons_run.c
 *
 *  Created on: 5 Nov 2022
 *      Author: HP PV
 */


#include "fsm_simple_buttons_run.h"

int status = COUNT_DOWN;

int counter = 9;

void fsm_simple_buttons_run(){
	switch(status){
	case INIT:
		display7SEG(counter);
		if(timer1_flag == 1){
			HAL_GPIO_TogglePin(Led_Red_GPIO_Port, Led_Red_Pin);
			setTimer1(1000);
		}

		status = NUM0;
		break;
	case NUM0:
		display7SEG(counter);
		if(timer1_flag == 1){
			HAL_GPIO_TogglePin(Led_Red_GPIO_Port, Led_Red_Pin);
			setTimer1(1000);
		}

		if(timer2_flag == 1 && counter != 0){
			status = COUNT_DOWN;
			setTimer2(5000);
		}

		if(isButton1Pressed() == 1){
			counter = 0;
			status = NUM0;
		}

		if(isButton2Pressed() == 1){
			status = INCMODE;
		}

		if(isButton3Pressed() == 1){
			status = DECMODE;
		}
		break;
	case COUNT_DOWN:
		display7SEG(counter);
		if(timer1_flag == 1){
			HAL_GPIO_TogglePin(Led_Red_GPIO_Port, Led_Red_Pin);
			setTimer1(1000);
		}

		if(timer2_flag == 1 && counter > 0){
			counter--;
			status = COUNT_DOWN;
			setTimer2(1000);
		}

		if(counter == 0)
			status = NUM0;

		if(isButton1Pressed() == 1){
			counter = 0;
			status = NUM0;
		}

		if(isButton2Pressed() == 1)
			status = INCMODE;

		if(isButton3Pressed() == 1)
			status = DECMODE;
		break;
	case INCMODE:
		display7SEG(counter);
		if(timer1_flag == 1){
			HAL_GPIO_TogglePin(Led_Red_GPIO_Port, Led_Red_Pin);
			setTimer1(1000);
		}

		if(counter >= 9)
			counter = 0;
		else
			counter++;
		status = COUNT_DOWN;
		setTimer2(5000);
		break;
	case DECMODE:
		display7SEG(counter);
		if(timer1_flag == 1){
			HAL_GPIO_TogglePin(Led_Red_GPIO_Port, Led_Red_Pin);
			setTimer1(1000);
		}

		if(counter <= 0)
			counter = 9;
		else
			counter--;
		status = COUNT_DOWN;
		setTimer2(5000);
		break;
	default:
		break;
	}
}
