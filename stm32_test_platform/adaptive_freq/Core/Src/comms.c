/*
 * comms.c
 *
 *  Created on: Aug 27, 2022
 *      Author: Kamil
 */
#include "stm32l4xx_hal.h"
// CAUTION! THE BANK SELECTION IS CURRENTLY DISABLED, SEE     static uint8_t read_single_icm20948_reg(userbank ub, uint8_t reg)
// INITIALIZATION PART IS ALSO OMITTED
#include "icm20948.h"

#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "freq_adjuster.h"

extern UART_HandleTypeDef huart1;

#define BUFFER_SIZE 20

char 	uart_rx_char;
char 	uart_in_buffer[BUFFER_SIZE];
char 	uart_out_buffer[BUFFER_SIZE];
int  	rx_buffer_position   = 0;
uint8_t buffer_ready_to_read = 0;


char order_set_freq[] = "freq";
char order_get_id[]   = "id";		// currently unused
char order_get_id01[] = "id01";
char order_ok[]       = "ok";

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	uart_in_buffer[ rx_buffer_position ] = uart_rx_char;
	if (uart_rx_char == '.' ){
		buffer_ready_to_read = 1;
		rx_buffer_position   = 0;
	}else{
		rx_buffer_position   += 1;								// if text is large enough, the buffer may overflow!
		buffer_ready_to_read =  0;
	}
	HAL_UART_Receive_IT(&huart1, (uint8_t *)&uart_rx_char, 1);				// reset it
}


void interpret_user_input(){
	if (buffer_ready_to_read == 0)
		return;
	buffer_ready_to_read = 0;
	char order[BUFFER_SIZE/2];		// local order buffer
	char argmnt[BUFFER_SIZE/2];		// local argument buffer
	int  index = 0;					// index in buffer
	int  phase = 0;					// 0-order 1-argmnt 2-end
	int  i;							// itereator


	// divides input in form of "ABC:12." into order ABC, argument 12
	for( i=0 ; i<BUFFER_SIZE ; i++){
		if( uart_in_buffer[i] == ':' ){
			phase = 1;
			order[index] = '\0';
			index = 0;
			continue;
		}else if( uart_in_buffer[i] == '.' ){
			if(phase == 0)
				order[index] = '\0';
			phase = 2;
			argmnt[index] = '\0';
		}else if (phase == 0){
			order[index] = uart_in_buffer[i];
		}else if (phase == 1){
			argmnt[index] = uart_in_buffer[i];
		}else if (phase == 2){
			break;
		}
		index++;
	}

	if(strcmp(order, order_set_freq) == 0){
		int desired_frequency = atoi(argmnt);
		CPU_set_freq(desired_frequency, &huart1);
		HAL_UART_Receive_IT(&huart1, (uint8_t *)&uart_rx_char, 1);	// reset it
		sprintf(uart_out_buffer, "\nOK\n");
		HAL_UART_Transmit(&huart1, (uint8_t *)uart_out_buffer, strlen(uart_out_buffer), 1000);
	}

//	if(strcmp(order, order_get_id) == 0){
//		uint8_t read_id = get_icm20948_id();
//		sprintf(uart_out_buffer, "\nOK\n0x%02x\n", read_id);
//		HAL_UART_Transmit(&huart1, (uint8_t *)uart_out_buffer, strlen(uart_out_buffer), 1000);
//	}

	if(strcmp(order, order_get_id01) == 0){
		uint8_t result = icm20948_who_am_i();
		sprintf(uart_out_buffer, "\nOK\n%d\n", result);
		HAL_UART_Transmit(&huart1, (uint8_t *)uart_out_buffer, strlen(uart_out_buffer), 1000);
	}

	if(strcmp(order, order_ok) == 0){
		sprintf(uart_out_buffer, "\nOK\n");
		HAL_UART_Transmit(&huart1, (uint8_t *)uart_out_buffer, strlen(uart_out_buffer), 1000);
	}
}
