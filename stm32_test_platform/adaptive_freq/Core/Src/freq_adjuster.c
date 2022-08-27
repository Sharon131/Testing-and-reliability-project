/*
 * freq_adjuster.c
 *
 *  Created on: Jul 5, 2022
 *      Author: Kamil
 */
#include "stm32l4xx_hal.h"

extern HAL_StatusTypeDef HAL_RCC_DeInit();
extern HAL_StatusTypeDef HAL_PWREx_ControlVoltageScaling(uint32_t VoltageScaling);
extern void Error_Handler(void);
extern HAL_StatusTypeDef HAL_RCC_OscConfig(RCC_OscInitTypeDef  *RCC_OscInitStruct);
extern void MX_USART1_UART_Init(void);	//<< UWAGA! nie moze byc static w mainie!

// freq range: 1-80 MHz
void CPU_set_freq(uint8_t freq, UART_HandleTypeDef *uart_to_reset){

	//DEINIT + DEFAULT
	HAL_RCC_DeInit();
	  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)	  {		Error_Handler();	  }


	  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)	  {		Error_Handler();	  }


	  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
								  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV8;
	  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)	  {		Error_Handler();	  }


	if( (freq >= 0)  &  (freq <= 5) ){
		 if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)			  {				Error_Handler();			  }


			  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
			  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
			  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
			  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
			  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
			  RCC_OscInitStruct.PLL.PLLM = 4;
			  switch(freq){
			  case 2:
				  RCC_OscInitStruct.PLL.PLLN = 32;
				  break;
			  case 3:
				  RCC_OscInitStruct.PLL.PLLN = 48;
				  break;
			  case 4:
				  RCC_OscInitStruct.PLL.PLLN = 64;
				  break;
			  case 5:
				  RCC_OscInitStruct.PLL.PLLN = 80;
				  break;
			  default:
				  RCC_OscInitStruct.PLL.PLLN = 16;
			  }
			  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
			  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
			  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV8;
			  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)			  {				Error_Handler();			  }


			  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
										  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
			  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV8;
			  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
			  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

			  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)			  {				Error_Handler();			  }

	}else if( (freq >= 6) & (freq <= 16)){
		  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)		  {		    Error_Handler();		  }

		  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
		  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
		  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
		  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
		  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
		  RCC_OscInitStruct.PLL.PLLM = 4;
		  switch(freq){
		  case 6:
			  RCC_OscInitStruct.PLL.PLLN = 24;
			  break;
		  case 7:
			  RCC_OscInitStruct.PLL.PLLN = 28;
			  break;
		  case 8:
			  RCC_OscInitStruct.PLL.PLLN = 32;
			  break;
		  case 9:
			  RCC_OscInitStruct.PLL.PLLN = 36;
			  break;
		  case 10:
			  RCC_OscInitStruct.PLL.PLLN = 40;
			  break;
		  case 11:
			  RCC_OscInitStruct.PLL.PLLN = 44;
			  break;
		  case 12:
			  RCC_OscInitStruct.PLL.PLLN = 48;
			  break;
		  case 13:
			  RCC_OscInitStruct.PLL.PLLN = 52;
			  break;
		  case 14:
			  RCC_OscInitStruct.PLL.PLLN = 56;
			  break;
		  case 15:
			  RCC_OscInitStruct.PLL.PLLN = 60;
			  break;
		  case 16:
			  RCC_OscInitStruct.PLL.PLLN = 64;
			  break;
		  }
		  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
		  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
		  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV8;
		  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)		  {		    Error_Handler();		  }


		  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
	  	  	  	  	  	  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
		  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
		  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
		  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
		  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

		  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)		  {		    Error_Handler();		  }
	}else if( (freq >= 17) & (freq <= 33)){
		  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)		  {		    Error_Handler();		  }


		  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
		  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
		  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
		  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
		  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
		  RCC_OscInitStruct.PLL.PLLM = 4;
		  RCC_OscInitStruct.PLL.PLLN = freq;
		  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
		  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
		  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV4;
		  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)		  {		    Error_Handler();		  }


		  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
	  	  	  	  	  	  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
		  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
		  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
		  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
		  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

		  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)		  {		    Error_Handler();		  }
	}else if( (freq >= 34) & (freq <= 49)){
		  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)		  {		    Error_Handler();		  }


		  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
		  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
		  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
		  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
		  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
		  RCC_OscInitStruct.PLL.PLLM = 4;
		  RCC_OscInitStruct.PLL.PLLN = freq;
		  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
		  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
		  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV4;
		  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)		  {		    Error_Handler();		  }


		  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
	  	  	  	  	  	  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
		  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
		  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
		  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
		  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

		  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)		  {		    Error_Handler();		  }
	}else if( (freq >= 50) & (freq <= 64)){
		  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)		  {		    Error_Handler();		  }


		  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
		  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
		  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
		  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
		  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
		  RCC_OscInitStruct.PLL.PLLM = 4;
		  RCC_OscInitStruct.PLL.PLLN = freq;
		  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
		  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
		  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV4;
		  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)		  {		    Error_Handler();		  }


		  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
	  	  	  	  	  	  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
		  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
		  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
		  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
		  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

		  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)		  {		    Error_Handler();		  }
	}else if( (freq >= 65) /*& (freq <= 80)*/){
		if(freq > 80) freq = 80;
		  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)		  {		    Error_Handler();		  }


		  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
		  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
		  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
		  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
		  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
		  RCC_OscInitStruct.PLL.PLLM = 4;
		  RCC_OscInitStruct.PLL.PLLN = freq;
		  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
		  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
		  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV4;
		  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)		  {		    Error_Handler();		  }


		  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
	  	  	  	  	  	  	  	  	  	  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
		  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
		  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
		  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
		  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

		  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)		  {		    Error_Handler();		  }
	}

		SystemCoreClockUpdate();
		HAL_UART_Abort(uart_to_reset);
		HAL_UART_DeInit(uart_to_reset);
		MX_USART1_UART_Init();
}
