#ifndef GFX_GC9A01_H
#define GFX_GC9A01_H

#include <stdint.h>

#ifndef GC9A01_XSTART
#define GC9A01_XSTART   	0
#endif
#ifndef GC9A01_YSTART
#define GC9A01_YSTART   	0
#endif

#define LCD_SPI_PORT 1
#define LCD_SPI_TIMEOUT 100

#define GC9A01_INVOFF		    0x20
#define GC9A01_INVON		    0x21
#define GC9A01_DISPON		    0x29
#define GC9A01_CASET		    0x2A
#define GC9A01_RASET		    0x2B
#define GC9A01_RAMWR		    0x2C
#define GC9A01_RAMWRNX		    0x3C
#define GC9A01_COLMOD		    0x3A
#define GC9A01_COLMOD_12_BIT    0x03
#define GC9A01_COLMOD_16_BIT    0x05
#define GC9A01_COLMOD_18_BIT    0x06
#define GC9A01_MADCTL		    0x36
#define GC9A01_MADCTL_MY  	    0x80
#define GC9A01_MADCTL_MX  	    0x40
#define GC9A01_MADCTL_MV  	    0x20
#define GC9A01_MADCTL_RGB 	    0x00
#define GC9A01_DISFNCTRL	    0xB6

void GC9A01_SetRstState(int PinState);
void GC9A01_SetDcState(int PinState);
void GC9A01_SetCsState(int PinState);
void GC9A01_TransmitData(uint8_t *pData, uint16_t Size, uint32_t Timeout);
void GC9A01_WriteData(uint8_t *pData, uint16_t Size);

void GC9A01_WriteCommand(uint8_t Cmd);
void GC9A01_WriteByte(uint8_t pData);
void GC9A01_Write(uint8_t *pAddr, uint16_t Size);
void GC9A01_WriteNext(uint8_t *pAddr, uint16_t Size);

void GC9A01_Init(void);
uint16_t GC9A01_Color565(uint8_t r, uint8_t g, uint8_t b);
void GC9A01_invertDisplay(int i);
void GC9A01_SetFrame(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

#endif
