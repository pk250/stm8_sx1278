#ifndef __USR_PUBLIC__
#define __USR_PUBLIC__

#include "stm8l15x.h"
#include "wh_usart.h"
#include "wh_spi.h"
#include "wh_tim.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

#include "radio.h"
#include "sx1276-LoRa.h"
#include "sx1276-LoRaMisc.h"
#include "sx1276-Hal.h"


#define BUF_LEN 255



#ifdef USR_MAIN
	#define MAIN_EXT
#else
	#define MAIN_EXT extern
#endif


/* UART Tx/Rx */
MAIN_EXT uint8_t RxBuffer[BUF_LEN];
MAIN_EXT uint16_t UartRxLen;
MAIN_EXT bool UartRxDone;
MAIN_EXT uint8_t TxBuffer[BUF_LEN];


/* LoRa */
MAIN_EXT uint16_t LoRaBufSize;			// RF buffer size
MAIN_EXT uint8_t LoRaBuffer[BUF_LEN];	// RF buffer
MAIN_EXT tRadioDriver *Radio;

void Delay_ms(uint16_t nCount);



#endif

