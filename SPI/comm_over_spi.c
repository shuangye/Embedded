typedef unsigned char byte_t;
typedef int           int32_t;


///////////////////////////////// spi_message.h /////////////////////////////////

#define SPI_MTU  512

typedef struct 
{
	uint32_t    seq;
	uint32_t    checksum;
} Spi_MessageHeader;

typedef struct 
{
	Spi_MessageHeader   header;
	byte_t              body[SPI_MTU - sizeof(Spi_MessageHeader)];
} Spi_Message;


///////////////////////////////// spi_message.c /////////////////////////////////
#include "spi_message.h"

int Spi_constructMessage(Spi_Message *message)
{
	/* fill body, seq, and calc checksum */
}

int Spi_checkMessage(const Spi_Message *message)
{
	/* check seq, checksum */
}



///////////////////////////////// spi_master.c /////////////////////////////////
#include "spi_message.h"

static Spi_Message gTxMessage, gRxMessage;


int Spi_masterInit(void)
{
	/* init SPI as master mode */
}

static int Spi_masterSetupDma(void)
{
	/* for TX: set DMA source addr = &gTxMessage, dest addr = SPI TX data register */

	/* for RX: set DMA source addr = SPI RX data register, dest addr = &gRxMessage */
}


static void Spi_masterXreqIsr(void)
{
	Spi_constructMessage(&gTxMessage);

	Spi_masterSetupDma();

	/* start SPI clocking and initiate SPI transfer */
}


static void Spi_masterDmaEndIsr(void)
{
	/* read received data from gRxMessage */
}


///////////////////////////////// spi_slave.c /////////////////////////////////
#include "spi_message.h"

static Spi_Message gTxMessage, gRxMessage;


int Spi_slaveInit(void)
{
	/* init SPI as slave mode */
	/* setup a timer, to trigger the periodic communication */
}


static int Spi_slaveSetupDma(void)
{
	/* for TX: set DMA source addr = &gTxMessage, dest addr = SPI TX data register */

	/* for RX: set DMA source addr = SPI RX data register, dest addr = &gRxMessage */
}


static void Spi_slaveDmaEndIsr(void)
{
	/* read received data from gRxMessage */
}


static void Spi_slaveTimerIsr(void)
{
	Spi_constructMessage(&gTxMessage);

	Spi_slaveSetupDma();

	/* assert XREQ signal */
}


