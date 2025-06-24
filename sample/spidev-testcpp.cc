#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <spidev_lib++.h>

#define CONTENT "hello world"
#define RX_BUFFER_LEN 32
#define TX_BUFFER_LEN 32

static spi_config_t spi_config;
static uint8_t tx_buffer[TX_BUFFER_LEN];
static uint8_t rx_buffer[RX_BUFFER_LEN];


int  main( void)
{

  SPI *mySPI = NULL;

  spi_config.mode=0;
  spi_config.speed=1000000;
  spi_config.delay=0;
  spi_config.bits_per_word=8;

  mySPI=new SPI("/dev/spidev1.0",&spi_config);


  if (mySPI->begin())
  {
    size_t content_len = sizeof(CONTENT);

    memcpy(tx_buffer, CONTENT, content_len);
    printf("sending %s, to spidev2.0 in full duplex \n ",tx_buffer);
    mySPI->xfer(tx_buffer,content_len,rx_buffer,RX_BUFFER_LEN);
    printf("rx_buffer=%s\n",(char *)rx_buffer);
    mySPI->end();
    delete mySPI;
  }
 return 1;
}
