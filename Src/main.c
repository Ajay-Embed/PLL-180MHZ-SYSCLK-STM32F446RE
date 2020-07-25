/*
MIT License

Copyright (c) [2020] [AJAY RAJAN]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include<string.h>
#include<stdio.h>
#include "stm32f4xx_hal.h"
#include "main.h"
#define TRUE 1
#define FALSE 1
void SystemClockConfig_HSE(uint8_t clock_freq);
void UART2_Init(void);
void Error_handler(void);


UART_HandleTypeDef huart2;

int main(void)
{

char msg[100];

	HAL_Init();
	SystemClockConfig_HSE(SYS_CLOCK_FREQ_180_MHZ);

	UART2_Init();


	memset(msg, 0, sizeof(msg));
	sprintf(msg, "SYSCLK = %ld\r\n", HAL_RCC_GetSysClockFreq());
	HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

	memset(msg, 0, sizeof(msg));
	sprintf(msg, "HCLK = %ld\r\n", HAL_RCC_GetHCLKFreq());
	HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);


	memset(msg, 0, sizeof(msg));
	sprintf(msg, "PCLK1 = %ld\r\n", HAL_RCC_GetPCLK1Freq());
	HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);


	memset(msg, 0, sizeof(msg));
	sprintf(msg, "PCLK2 = %ld\r\n", HAL_RCC_GetPCLK2Freq());
	HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);





	while(1);


	return 0;
}




void UART2_Init(void)
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	if ( HAL_UART_Init(&huart2) != HAL_OK )
	{
		//There is a problem
		Error_handler();
	}


}

void SystemClockConfig_HSE(uint8_t clock_freq)
{

	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;
uint32_t Flatency = 0;

	osc_init.OscillatorType			= RCC_OSCILLATORTYPE_HSE;
	osc_init.HSEState				= RCC_HSE_BYPASS; //FOR STM32F446RE MCU, HSE IS FROM ST-LINK CIRCUITRY... THEREFORE BYPASS
	//NO CALIBRATION REQUIRED FOR HSE
	osc_init.PLL.PLLState			= RCC_PLL_ON;
	osc_init.PLL.PLLSource			= RCC_PLLSOURCE_HSE;



	switch(clock_freq)
	{
	case SYS_CLOCK_FREQ_50_MHZ:
	{
		osc_init.PLL.PLLM 		= 8;
		osc_init.PLL.PLLN		= 100;
		osc_init.PLL.PLLP		= 2;
		osc_init.PLL.PLLR		= 2;
		osc_init.PLL.PLLQ		= 2;




		clk_init.ClockType 				= RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
		clk_init.SYSCLKSource			= RCC_SYSCLKSOURCE_PLLCLK;
		clk_init.AHBCLKDivider			= RCC_SYSCLK_DIV1;
		clk_init.APB1CLKDivider			= RCC_HCLK_DIV2;
		clk_init.APB2CLKDivider			= RCC_HCLK_DIV2;

		Flatency = FLASH_ACR_LATENCY_1WS;

		break;
	}
	case SYS_CLOCK_FREQ_84_MHZ:
	{
				osc_init.PLL.PLLM 		= 8;
				osc_init.PLL.PLLN		= 168;
				osc_init.PLL.PLLP		= 2;
				osc_init.PLL.PLLR		= 2;
				osc_init.PLL.PLLQ		= 2;



				clk_init.ClockType 				= RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
				clk_init.SYSCLKSource			= RCC_SYSCLKSOURCE_PLLCLK;
				clk_init.AHBCLKDivider			= RCC_SYSCLK_DIV1;
				clk_init.APB1CLKDivider			= RCC_HCLK_DIV4;
				clk_init.APB2CLKDivider			= RCC_HCLK_DIV2;

				Flatency = FLASH_ACR_LATENCY_2WS;


				break;
	}
	case SYS_CLOCK_FREQ_120_MHZ:
	{
					osc_init.PLL.PLLM 		= 8;
					osc_init.PLL.PLLN		= 240;
					osc_init.PLL.PLLP		= 2;
					osc_init.PLL.PLLR		= 2;
					osc_init.PLL.PLLQ		= 2;



					clk_init.ClockType 				= RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
					clk_init.SYSCLKSource			= RCC_SYSCLKSOURCE_PLLCLK;
					clk_init.AHBCLKDivider			= RCC_SYSCLK_DIV1;
					clk_init.APB1CLKDivider			= RCC_HCLK_DIV2;
					clk_init.APB2CLKDivider			= RCC_HCLK_DIV2;

					Flatency = FLASH_ACR_LATENCY_3WS;


					break;
	}


	case SYS_CLOCK_FREQ_180_MHZ:
	{

		/*
		 * For 180mhz, you have to enable voltage scaling and also put the micro-controller in over-drive mode
		 * from Power control register---------------> PWR_CR
		 *
		 */

		//Enable the clk for pwer controller

		__HAL_RCC_PWR_CLK_ENABLE();


		//Set regulator voltage scale as 1
		__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);


		//Turn on the overdrive mode
		__HAL_PWR_OVERDRIVE_ENABLE();

					osc_init.PLL.PLLM 		= 8;
					osc_init.PLL.PLLN		= 360;
					osc_init.PLL.PLLP		= 2;
					osc_init.PLL.PLLR		= 2;
					osc_init.PLL.PLLQ		= 2;



					clk_init.ClockType 				= RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
					clk_init.SYSCLKSource			= RCC_SYSCLKSOURCE_PLLCLK;
					clk_init.AHBCLKDivider			= RCC_SYSCLK_DIV1;
					clk_init.APB1CLKDivider			= RCC_HCLK_DIV2;
					clk_init.APB2CLKDivider			= RCC_HCLK_DIV2;

					Flatency = FLASH_ACR_LATENCY_5WS;


					break;
	}



	default:
		return;



	}




if(HAL_RCC_OscConfig(&osc_init) != HAL_OK)
{
	Error_handler();
}




if(HAL_RCC_ClockConfig(&clk_init, Flatency) != HAL_OK)
{
	Error_handler();
}



//SYSTICK CONFIGURATION
HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

}

void Error_handler(void)
{
	while(1);
}
