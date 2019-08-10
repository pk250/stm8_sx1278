/**
  ******************************************************************************
  * @file    Project/STM8L15x_StdPeriph_Template/main.c
  * @author  MCD Application Team
  * @version V1.6.1
  * @date    30-September-2014
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */
#define USR_MAIN

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "wh_public.h"
#include "sx1276-Hal.h"


/** @addtogroup STM8L15x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void CLK_Config( void );

/* Private functions ---------------------------------------------------------*/

uint32_t cnt = 0;
static void LoRaProcess( void )
{	
    switch( Radio->Process( ) )
    {
    case RF_RX_TIMEOUT:
		//printf("\r\nRF_RX_TIMEOUT\r\n");
		wh_lora_send("WenHeng", strlen("WenHeng"));

        break;
		
    case RF_RX_DONE:
		//printf("\r\nGetRxPacket\r\n");
        Radio->GetRxPacket( LoRaBuffer, &LoRaBufSize );
        if( LoRaBufSize > 0 )
        {
			if(memcmp("WenHeng", LoRaBuffer, strlen("WenHeng")) == 0)
			{
				printf("\r\nRecv count: %lu\r\n", ++cnt);
			}
        }
		Radio->StartRx( );
		
        break;
		
    case RF_TX_DONE:
		//printf("\r\nTxDone\r\n");
        Radio->StartRx( );
		
        break;
		
    default:
        break;
    }
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */

void main(void)
{
	/* Clock */
	CLK_Config();

	USART_Config();
	SPI_Config();
	TIM4_Config();

	/* Init SX1278 */  
	Radio = RadioDriverInit( );	
	Radio->Init( );
	Radio->StartRx( );
	
	printf("\r\nWH-LR30 demo starting...\r\n");

	/* Infinite loop */
	
	while (1)
	{
		LoRaProcess();
	}
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


static void CLK_Config(void)
{
	/* Select HSI as system clock source */
	CLK_SYSCLKSourceSwitchCmd(ENABLE);	
	CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);
	
	/* system clock prescaler: 1*/
	CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
	while (CLK_GetSYSCLKSource() != CLK_SYSCLKSource_HSI);
	
	/* Enable USART clock */
	CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE);
	
	/* Enable DMA clock */
	CLK_PeripheralClockConfig(CLK_Peripheral_DMA1, ENABLE);

	/* Enable SPI clock */
	CLK_PeripheralClockConfig(CLK_Peripheral_SPI1, ENABLE);
	
	/* Enable TIM4 CLK */
  	CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, ENABLE);
}

int fputc(int ch, FILE *f)
{
	uint8_t tmp = ch;
	
	USART_SendData8(COM_OBJ, tmp);
	while (USART_GetFlagStatus(COM_OBJ, USART_FLAG_TC) == RESET);

	return ch;
}

void Delayus(void)   
{    
    asm("nop");
    asm("nop");   
    asm("nop");   
    asm("nop");    
}   

void Delay_ms(uint16_t nCount)  
{
	uint16_t i;   
    while(nCount--)     
    for(i=900;i>0;i--)   
    	Delayus(); 
} 

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
