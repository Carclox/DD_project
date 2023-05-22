/*
 * machine_control.h
 *
 *  Created on: Apr 29, 2023
 *      Author: vapat
 */

#ifndef INC_MACHINE_CONTROL_H_
#define INC_MACHINE_CONTROL_H_

#define LED_OFF 				HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
#define LED_ON 					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);


#include "main.h"

typedef enum{
	S0,
	S1,
	S2,
	S3,
	S4
}machine_state;

void led_off (void);
void led_blink_5hz(void);
void led_blink_2hz(void);
void led_blink_1hz(void);
void led_blink_05hz(void);

void machine_states( void );
void change_to_next_state( void );
void intialize_machine_states( void );
void compare_string( void );
void comand_verify(void);


#endif /* INC_MACHINE_CONTROL_H_ */
