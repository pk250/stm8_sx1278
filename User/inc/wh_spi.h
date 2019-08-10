#ifndef __USR_SPI__
#define __USR_SPI__

#define SPI_PORT		GPIOB
#define SPI_MISO_PIN	GPIO_Pin_7
#define SPI_MOSI_PIN	GPIO_Pin_6
#define SPI_CLK_PIN		GPIO_Pin_5
#define SPI_CS_PIN		GPIO_Pin_4

void SPI_Config(void);
uint8_t SpiInOut( uint8_t outData );


#endif
