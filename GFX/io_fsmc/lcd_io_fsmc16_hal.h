//=============================================================================
/* Information section */

/*
 * 16 bit paralell LCD FSMC driver
 * 5 controll pins (CS, RS, WR, RD, RST) + 16 data pins + backlight pin
 * FSMC_NE1..NE4<-LCD_CS, FSMC_NOE<-LCD_RD, FSMC_NWE<-LCD_WR, FSMC_Ax<-LCD_RS
 * FSMC_D0<-LCD_D0, FSMC_D1<-LCD_D1, FSMC_D2<-LCD_D2, FSMC_D3<-LCD_D3
 * FSMC_D4<-LCD_D4, FSMC_D5<-LCD_D5, FSMC_D6<-LCD_D6, FSMC_D7<-LCD_D7
 * FSMC_D8<-LCD_D8, FSMC_D9<-LCD_D9, FSMC_D10<-LCD_D10, FSMC_D11<-LCD_D11
 * FSMC_D12<-LCD_D12, FSMC_D13<-LCD_D13, FSMC_D14<-LCD_D14, FSMC_D15<-LCD_D15
 */

/* Settings in CUBEIDE or CUBEMX
   FMC / FSMC
   - select the bank
   - select Chip Select
   - select Memory type: LCD Interface
   - select LCD Register Select: which pin we connected to the LCD RS pin
   - select Data: 16 bits
   - NOR/PSRAM Write operation: Enabled
   - NOR/PSRAM Extended mode: Disabled
   - NOR/PSRAM timings: first give a higher value, later if it works well, reduce it until it works well
   GPIO
   - Lcd reset pin (only when connected)
     - output level: High
     - mode: Output Push Pull
     - Pull-up/Pull-down: No pull-up and no pull-down
     - Max output speed: Low
     - User Label: LCD_RST
   - Lcd back light pin (only when connected)
     - output level: Low or High
     - mode: Output Push Pull
     - Pull-up/Pull-down: No pull-up and no pull-down
     - Max output speed: Low
     - User Label: LCD_BL

   Settings in main.h:
   - If you use freertos, add this line the main.h file
     #include "cmsis_os.h"
     (note: then the driver will also use the rtos signal to wait for the end of the dma transaction)
*/

#ifndef __LCD_IO_FSMC16_H
#define __LCD_IO_FSMC16_H

void LCD_IO_DmaTxCpltCallback(DMA_HandleTypeDef *hdma);
void LCD_IO_DmaRxCpltCallback(DMA_HandleTypeDef *hdma);

//=============================================================================
/* Memory address
  - Bank1 (NE1) 0x60000000
  - Bank2 (NE2) 0x64000000
  - Bank3 (NE3) 0x68000000
  - Bank4 (NE4) 0x6C000000
  - LCD_REGSELECT_BIT: to which address wire the LCD_RS pin is connected (if the LCD Register Select: A18 -> 18) */
#define LCD_ADDR_BASE         0x60000000
#define LCD_REGSELECT_BIT     18

/* Data direction
   - 0: only draw mode
   - 1: bidirectional mode */
#define LCD_DATADIR           1

/* DMA */
#define LCD_DMA_TX            0
#define LCD_DMA_RX            0

/* Memory to memory DMA handle name (see in main.c) */
#define LCD_DMA_HANDLE        hdma_memtomem_dma2_stream0

/* In dma mode the bitmap drawing function is completed before the actual drawing.
   When should we wait for the previous DMA operation to complete? (see the readme.me file)
   - 0: DMA check and wait at drawing function start
   - 1: DMA check and wait at drawing function start + bitmap drawing function end wait on (default mode)
   - 2: DMA wait at drawing function end */
#define LCD_DMA_ENDWAIT       1

/* Because there are DMA capable and DMA unable memory regions
   here we can set what is the DMA unable region condition
   note: where the condition is true, it is considered a DMA-unable region
   Default (all memory used for bitmap drawing is DMA capable):
     #define LCD_DMA_UNABLE(addr)  0
   Example stm32f407 and stm32f429 with CCMRAM (the CCMRAM is not DMA capable):
     #define LCD_DMA_UNABLE(addr)  ((addr < 0x20000000) && (addr >= 0x10000000))
   Example stm32h743 (the DTCMRAM and ITCMRAM are not DMA capable):
     #define LCD_DMA_UNABLE(addr)  (((addr < 0x24000000) && (addr >= 0x20000000)) || (addr < 0x08000000))
   Note: if we ensure that we do not draw a bitmap from a DMA-capable memory area, it is not necessary to set it (leave it that way) */
#define LCD_DMA_UNABLE(addr)  0

/* RGB565 to RGB888 and RGB888 to RGB565 convert byte order
   - 0: forward direction
   - 1: back direction
   note: If the red and blue colors are reversed and used 24bit mode, change this value */
#define LCD_RGB24_ORDER       0

/* 24bit color write mode and read mode (ILI9341: if MDT=="00"-> 0, if MDT=="01"->1) */
#define LCD_RGB24_MODE        0

#endif // __LCD_IO_FSMC8_H