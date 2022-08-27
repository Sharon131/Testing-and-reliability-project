/*
 * comms.h
 *
 *  Created on: Aug 27, 2022
 *      Author: Kamil
 */

#ifndef INC_COMMS_H_
#define INC_COMMS_H_
#include "stm32l4xx_hal.h"

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void interpret_user_input();


#endif /* INC_COMMS_H_ */
