/**
  ******************************************************************************
  * File Name          : SPI.c
  * Description        : This file provides code for the configuration
  *                      of the SPI instances.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "wh_public.h"
#include "wh_spi.h"

void SPI_Config(void)
{   
	//Config SPI_PIN
    GPIO_Init(SPI_PORT, SPI_MOSI_PIN, GPIO_Mode_Out_PP_High_Fast);
	GPIO_Init(SPI_PORT, SPI_MISO_PIN, GPIO_Mode_In_PU_No_IT);
    GPIO_Init(SPI_PORT, SPI_CLK_PIN,  GPIO_Mode_Out_PP_High_Fast);   
    GPIO_Init(SPI_PORT, SPI_CS_PIN,   GPIO_Mode_Out_PP_High_Fast);  

    /* Init SPI */  
    SPI_Init(SPI1, SPI_FirstBit_MSB, SPI_BaudRatePrescaler_2, SPI_Mode_Master, \
         SPI_CPOL_Low, SPI_CPHA_1Edge, \
        SPI_Direction_2Lines_FullDuplex, SPI_NSS_Soft, 0x07);  

	/* Enable SPI */
    SPI_Cmd(SPI1, ENABLE);
}

/* USER CODE BEGIN 1 */
uint8_t SpiInOut( uint8_t outData )
{
	/* Loop while DR register in not emplty */  
  while (SPI_GetFlagStatus(SPI1, SPI_FLAG_TXE) == RESET);  
  
  /* Send byte through the SPI1 peripheral */  
  SPI_SendData(SPI1, outData);  
  
  /* Wait to receive a byte */  
  while (SPI_GetFlagStatus(SPI1, SPI_FLAG_RXNE) == RESET);  
  
  /* Return the byte read from the SPI bus */  
  return SPI_ReceiveData(SPI1);   
}
