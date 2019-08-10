#ifndef __USR_USART__
#define __USR_USART__

#include "wh_public.h"

/* define the DMA parameters related to USART1 since USE_STM8L1526_EVAL is used */
#define USART_DMA_CHANNEL_RX   DMA1_Channel2
#define USART_DMA_CHANNEL_TX   DMA1_Channel1
#define USART_DMA_FLAG_TCRX    (uint16_t)DMA1_FLAG_TC2
#define USART_DMA_FLAG_TCTX    (uint16_t)DMA1_FLAG_TC1
#define USART_DR_ADDRESS       (uint16_t)0x5231  /* USART1 Data register Address */

#define COM_OBJ		USART1
#define COM_PORT	GPIOC
#define COM_TX_PIN	GPIO_Pin_3
#define COM_RX_PIN	GPIO_Pin_2
#define COM_485_PIN	GPIO_Pin_1

void USART_Config(void);
void wh_uart_send_stream(unsigned char *data, int len);
void wh_lora_send(unsigned char *data, unsigned short len);
void wh_uart_deal(void);


#endif

