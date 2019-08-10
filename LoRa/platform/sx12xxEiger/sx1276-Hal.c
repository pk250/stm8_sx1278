/*
 * THE FOLLOWING FIRMWARE IS PROVIDED: (1) "AS IS" WITH NO WARRANTY; AND 
 * (2)TO ENABLE ACCESS TO CODING INFORMATION TO GUIDE AND FACILITATE CUSTOMER.
 * CONSEQUENTLY, SEMTECH SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR
 * CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
 * OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION
 * CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 * 
 * Copyright (C) SEMTECH S.A.
 */
/*! 
 * \file       sx1276-Hal.c
 * \brief      SX1276 Hardware Abstraction Layer
 *
 * \version    2.0.B2 
 * \date       Nov 21 2012
 * \author     Miguel Luis
 *
 * Last modified by Miguel Luis on Jun 19 2013
 */

#include "platform.h"

/* add by usr zhangzhen */
#include "wh_public.h"

#define Bit_SET					SET
#define Bit_RESET				RESET

#if defined( USE_SX1276_RADIO )

#include "wh_spi.h"
#include "../../radio/sx1276-Hal.h"

/*!
 * SX1276 RESET I/O definitions
 */
#define RESET_IOPORT                                GPIOD
#define RESET_PIN                                   GPIO_Pin_4

/*!
 * SX1276 SPI NSS I/O definitions
 */
//#define NSS_IOPORT                                  GPIOB
//#define NSS_PIN                                     GPIO_Pin_4

/*!
 * SX1276 DIO pins  I/O definitions
 */
#define DIO0_IOPORT                                 GPIOB
#define DIO0_PIN                                    GPIO_Pin_3

#define DIO1_IOPORT                                 GPIOB
#define DIO1_PIN                                    GPIO_Pin_2

#define DIO2_IOPORT                                 GPIOB
#define DIO2_PIN                                    GPIO_Pin_1

#define DIO3_IOPORT                                 GPIOB
#define DIO3_PIN    								GPIO_Pin_0

#define DIO4_IOPORT                                 GPIOD
#define DIO4_PIN                                    GPIO_Pin_3

#define DIO5_IOPORT                                 GPIOD
#define DIO5_PIN    								GPIO_Pin_2


void SX1276InitIo( void )
{
	// Configure radio DIO as inputs
	GPIO_Init(DIO0_IOPORT, DIO0_PIN, GPIO_Mode_In_FL_No_IT);

	// Configure radio DI1 as inputs
	GPIO_Init(DIO1_IOPORT, DIO1_PIN, GPIO_Mode_In_FL_No_IT);

	// Configure radio DI2 as inputs
	GPIO_Init(DIO2_IOPORT, DIO2_PIN, GPIO_Mode_In_FL_No_IT);

	// Configure radio DI2 as inputs
	GPIO_Init(DIO3_IOPORT, DIO3_PIN, GPIO_Mode_In_FL_No_IT);

	// Configure radio DI2 as inputs
	GPIO_Init(DIO4_IOPORT, DIO4_PIN, GPIO_Mode_In_FL_No_IT);

	// Configure radio DI2 as inputs
	GPIO_Init(DIO5_IOPORT, DIO5_PIN, GPIO_Mode_In_FL_No_IT);
}

void SX1276SetReset( uint8_t state )
{
    // Configure radio DI2 as inputs
	GPIO_Init(RESET_IOPORT, RESET_PIN, GPIO_Mode_Out_PP_High_Fast);

    if( state == RADIO_RESET_ON )
    {
        // Set RESET pin to 0
		GPIO_WriteBit(RESET_IOPORT, RESET_PIN, Bit_RESET);
    }
    else
    {
		// Set RESET pin to 1
		GPIO_WriteBit(RESET_IOPORT, RESET_PIN, Bit_SET);
    }

}

void SX1276Write( uint8_t addr, uint8_t data )
{
    SX1276WriteBuffer( addr, &data, 1 );
}

void SX1276Read( uint8_t addr, uint8_t *data )
{
    SX1276ReadBuffer( addr, data, 1 );
}

void SX1276WriteBuffer( uint8_t addr, uint8_t *buffer, uint8_t size )
{
    uint8_t i;

    //NSS = 0;
    GPIO_WriteBit( SPI_PORT, SPI_CS_PIN, Bit_RESET );

    SpiInOut( addr | 0x80 );
    for( i = 0; i < size; i++ )
    {
        SpiInOut( buffer[i] );
    }

    //NSS = 1;
    GPIO_WriteBit( SPI_PORT, SPI_CS_PIN, Bit_SET );
}

void SX1276ReadBuffer( uint8_t addr, uint8_t *buffer, uint8_t size )
{
    uint8_t i;

    //NSS = 0;
    GPIO_WriteBit( SPI_PORT, SPI_CS_PIN, Bit_RESET );

    SpiInOut( addr & 0x7F );

    for( i = 0; i < size; i++ )
    {
        buffer[i] = SpiInOut( 0 );
    }

    //NSS = 1;
    GPIO_WriteBit( SPI_PORT, SPI_CS_PIN, Bit_SET );
}

void SX1276WriteFifo( uint8_t *buffer, uint8_t size )
{
    SX1276WriteBuffer( 0, buffer, size );
}

void SX1276ReadFifo( uint8_t *buffer, uint8_t size )
{
    SX1276ReadBuffer( 0, buffer, size );
}

inline uint8_t SX1276ReadDio0( void )
{
    return GPIO_ReadInputDataBit( DIO0_IOPORT, DIO0_PIN );
}

inline uint8_t SX1276ReadDio1( void )
{
    return GPIO_ReadInputDataBit( DIO1_IOPORT, DIO1_PIN );
}

inline uint8_t SX1276ReadDio2( void )
{
    return GPIO_ReadInputDataBit( DIO2_IOPORT, DIO2_PIN );
}

inline uint8_t SX1276ReadDio3( void )
{
    //return IoePinGet( RF_DIO3_PIN );
	return GPIO_ReadInputDataBit( DIO3_IOPORT, DIO3_PIN );
}

inline uint8_t SX1276ReadDio4( void )
{
    //return IoePinGet( RF_DIO4_PIN );
	return GPIO_ReadInputDataBit( DIO4_IOPORT, DIO4_PIN );
}

inline uint8_t SX1276ReadDio5( void )
{
    //return IoePinGet( RF_DIO5_PIN );
	return GPIO_ReadInputDataBit( DIO5_IOPORT, DIO5_PIN );
}

inline void SX1276WriteRxTx( uint8_t txEnable )
{
	//u_printf("*********SX1276WriteRxTx en:%d\r\n", txEnable);

}

#endif // USE_SX1276_RADIO
