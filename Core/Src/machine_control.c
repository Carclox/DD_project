/*
 * machine_control.c
 *
 *  Created on: Apr 29, 2023
 *      Author: vapat
 */

#include "machine_control.h"
#include <string.h>
#include <stdio.h>


machine_state frequency_state;
extern uint8_t counter_50ms;
extern UART_HandleTypeDef huart2;
extern char rx_buffer [RX_BUFFER_LEN] ;
extern uint8_t rx_position_counter;

void intialize_machine_states( void ){
	frequency_state = S1;
}

void machine_states( void ){
	switch ( frequency_state ){
		case S0:
			led_off();
			break;
		case S1:
			led_blink_5hz();
			break;
		case S2:
			led_blink_2hz();
			break;
		case S3:
			led_blink_1hz();
			break;
		case S4:
			led_blink_05hz();
	}
}

void led_off( void ){
	LED_OFF;
}

void led_blink_5hz( void ){
	if ( counter_50ms == 2 )
	{
		counter_50ms = 0;
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	}
}


void led_blink_2hz( void ){
	if ( counter_50ms == 5 )
	{
		counter_50ms = 0;
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	}
}

void led_blink_1hz( void ){
	if ( counter_50ms == 10 )
	{
		counter_50ms = 0;
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	}
}

void led_blink_05hz( void ){
	if ( counter_50ms == 20 )
	{
		counter_50ms = 0;
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	}
}

void change_to_next_state( void ){

	counter_50ms = 0;
	char data_to_transmit[TX_BUFFER_LEN];
	uint8_t str_len;

	switch ( frequency_state ){
			case S0:
				frequency_state = S1;
				str_len = sprintf(&data_to_transmit[0], " The frequency is: 5 Hz");
				HAL_UART_Transmit(&huart2, (const uint8_t *) &data_to_transmit[0], str_len, 1000);
				break;
			case S1:
				str_len = sprintf(&data_to_transmit[0], " The frequency is: 2 Hz");
				HAL_UART_Transmit(&huart2, (const uint8_t *) &data_to_transmit[0], str_len, 1000);
				frequency_state = S2;
				break;
			case S2:
				frequency_state = S3;
				str_len = sprintf(&data_to_transmit[0], " The frequency is: 1 Hz");
				HAL_UART_Transmit(&huart2, (const uint8_t *) &data_to_transmit[0], str_len, 1000);
				break;
			case S3:
				frequency_state = S4;
				str_len = sprintf(&data_to_transmit[0], " The frequency is: 0.5 Hz");
				HAL_UART_Transmit(&huart2, (const uint8_t *) &data_to_transmit[0], str_len, 1000);
				break;
			case S4:
				frequency_state = S0;
				str_len = sprintf(&data_to_transmit[0], " The LED is OFF");
				HAL_UART_Transmit(&huart2, (const uint8_t *) &data_to_transmit[0], str_len, 1000);
				break;
		}
}
 static void re_init_comunication (void){
	 HAL_UART_AbortReceive_IT(&huart2);
	 rx_position_counter = 0;
	 memset((void *) &rx_buffer[0], '\0', RX_BUFFER_LEN);
	 HAL_UART_Receive_IT(&huart2, (uint8_t *) &rx_buffer[rx_position_counter], 1);
 }
void compare_string( void ){

	 if ( strcmp("FR1" , &rx_buffer[0]) == 0 ){
		 frequency_state = S1;
		 comand_verify();
		 counter_50ms = 0;
		 re_init_comunication();
	 }
	 else if( strcmp("FREQ2" , &rx_buffer[0]) == 0 ){
		 frequency_state = S2;
		 comand_verify();
		 counter_50ms = 0;
		 re_init_comunication();
	 }
	 else if( strcmp("FR3" , &rx_buffer[0]) == 0 ){
		 frequency_state = S3;
		 comand_verify();
		 counter_50ms = 0;
		 re_init_comunication();
	 	}
	 else if( strcmp("FREQ4" , &rx_buffer[0]) == 0 ){
		 frequency_state = S4;
		 comand_verify();
		 counter_50ms = 0;
		 re_init_comunication();
	 }
	 else if( strcmp("OFF" , &rx_buffer[0]) == 0 ){
		 frequency_state = S0;
		 comand_verify();
		 counter_50ms = 0;
		 re_init_comunication();
	 }
 }


void comand_verify(void){
	char data_to_transmit[TX_BUFFER_LEN];
	uint8_t str_len;
	str_len = sprintf(&data_to_transmit[0], "Command received");
	HAL_UART_Transmit(&huart2, (const uint8_t *) &data_to_transmit[0], str_len, 1000);
}
