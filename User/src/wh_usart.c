#include "wh_public.h"
#include "wh_usart.h"
#include "stm8l15x.h"

void USART_Config(void)
{		
	/* Configure USART Tx as alternate function push-pull  (software pull up)*/
	GPIO_ExternalPullUpConfig(COM_PORT, COM_TX_PIN, ENABLE);

	/* Configure USART Rx as alternate function push-pull  (software pull up)*/
	GPIO_ExternalPullUpConfig(COM_PORT, COM_RX_PIN, ENABLE);

	/* USART configuration */
	USART_Init(COM_OBJ, 115200, USART_WordLength_8b, \
								USART_StopBits_1, 	\
								USART_Parity_No, 		\
								(USART_Mode_TypeDef)(USART_Mode_Tx));
	
	USART_Cmd(COM_OBJ, ENABLE);
}

void wh_lora_send(unsigned char *data, uint16_t len)
{
	Radio->SetTxPacket(data, len);
}


