/*
 * freq_adjustger.h
 *
 *  Created on: Jul 5, 2022
 *      Author: Kamil
 */

#ifndef INC_FREQ_ADJUSTER_H_
#define INC_FREQ_ADJUSTER_H_
#include "stm32l4xx_hal.h"
// freq range: 1-80 MHz
void CPU_set_freq(uint8_t freq, UART_HandleTypeDef *uart_to_reset);

#endif /* INC_FREQ_ADJUSTER_H_ */
