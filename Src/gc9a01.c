#include <stdint.h>

#include "stm32f4xx_ll_gpio.h"
#include "main.h"
#include "spi.h"

#include "gc9a01.h"

void GC9A01_SetRstState(int PinState)
{
    if ((GPIO_PinState)PinState != GPIO_PIN_RESET)
    {
        LL_GPIO_SetOutputPin(LCD_RST_GPIO_Port, LCD_RST_Pin);
    } else
    {
        LL_GPIO_ResetOutputPin(LCD_RST_GPIO_Port, LCD_RST_Pin);
    }
}

void GC9A01_SetDcState(int PinState)
{
    if ((GPIO_PinState)PinState != GPIO_PIN_RESET)
    {
        LL_GPIO_SetOutputPin(LCD_RS_GPIO_Port, LCD_RS_Pin);
    } else
    {
        LL_GPIO_ResetOutputPin(LCD_RS_GPIO_Port, LCD_RS_Pin);
    }
}

void GC9A01_SetCsState(int PinState)
{
    if ((GPIO_PinState)PinState != GPIO_PIN_RESET)
    {
        LL_GPIO_SetOutputPin(LCD_CS_GPIO_Port, LCD_CS_Pin);
    } else
    {
        LL_GPIO_ResetOutputPin(LCD_CS_GPIO_Port, LCD_CS_Pin);
    }
}

void GC9A01_TransmitData(uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    SPI_HandleTypeDef *hspi;

    #if defined(hspi2) && (LCD_SPI_PORT == 2)
    hspi = &hspi2;
    #elif defined(hspi3) && (LCD_SPI_PORT == 3)
    hspi = &hspi3;
    #else
    hspi = &hspi1;
    #endif

    if (hspi == NULL)
    {
        Error_Handler();
    }

    if (hspi->hdmatx != NULL)
    {
        if (Size < 0)
        {
            HAL_SPI_Transmit_DMA(hspi, pData, sizeof(pData));
        } else
        {
            HAL_SPI_Transmit_DMA(hspi, pData, Size);
        }
    } else
    {
        if (Size < 0)
        {
            HAL_SPI_Transmit(hspi, pData, sizeof(pData), Timeout);
        } else
        {
            HAL_SPI_Transmit(hspi, pData, Size, Timeout);
        }
    }
}

void GC9A01_WriteData(uint8_t *pData, uint16_t Size)
{
    GC9A01_SetDcState(GPIO_PIN_SET);
    GC9A01_SetCsState(GPIO_PIN_RESET);
    GC9A01_TransmitData(pData, Size, LCD_SPI_TIMEOUT);
    GC9A01_SetCsState(GPIO_PIN_SET);
}

void GC9A01_WriteCommand(uint8_t Cmd)
{
    GC9A01_SetDcState(GPIO_PIN_RESET);
    GC9A01_SetCsState(GPIO_PIN_RESET);
    GC9A01_TransmitData(&Cmd, sizeof(Cmd), LCD_SPI_TIMEOUT);
    GC9A01_SetCsState(GPIO_PIN_SET);
}

void GC9A01_WriteByte(uint8_t pData)
{
    GC9A01_WriteData(&pData, sizeof(pData));
}

void GC9A01_Write(uint8_t *pAddr, uint16_t Size)
{
    GC9A01_WriteCommand(GC9A01_RAMWR);
    GC9A01_WriteData(pAddr, Size);
}

void GC9A01_WriteNext(uint8_t *pAddr, uint16_t Size)
{
    GC9A01_WriteCommand(GC9A01_RAMWRNX);
    GC9A01_WriteData(pAddr, Size);
}

void GC9A01_Init(void)
{
    GC9A01_SetCsState(1);
    HAL_Delay(5);
    GC9A01_SetRstState(0);
    HAL_Delay(10);
    GC9A01_SetRstState(1);
    HAL_Delay(120);

    /* Initial Sequence */ 

    GC9A01_WriteCommand(0xEF);

    GC9A01_WriteCommand(0xEB);
    GC9A01_WriteByte(0x14);

    GC9A01_WriteCommand(0xFE);
    GC9A01_WriteCommand(0xEF);

    GC9A01_WriteCommand(0xEB);
    GC9A01_WriteByte(0x14);

    GC9A01_WriteCommand(0x84);
    GC9A01_WriteByte(0x40);

    GC9A01_WriteCommand(0x85);
    GC9A01_WriteByte(0xFF);

    GC9A01_WriteCommand(0x86);
    GC9A01_WriteByte(0xFF);

    GC9A01_WriteCommand(0x87);
    GC9A01_WriteByte(0xFF);

    GC9A01_WriteCommand(0x88);
    GC9A01_WriteByte(0x0A);

    GC9A01_WriteCommand(0x89);
    GC9A01_WriteByte(0x21);

    GC9A01_WriteCommand(0x8A);
    GC9A01_WriteByte(0x00);

    GC9A01_WriteCommand(0x8B);
    GC9A01_WriteByte(0x80);

    GC9A01_WriteCommand(0x8C);
    GC9A01_WriteByte(0x01);

    GC9A01_WriteCommand(0x8D);
    GC9A01_WriteByte(0x01);

    GC9A01_WriteCommand(0x8E);
    GC9A01_WriteByte(0xFF);

    GC9A01_WriteCommand(0x8F);
    GC9A01_WriteByte(0xFF);

    GC9A01_WriteCommand(0xB6);
    GC9A01_WriteByte(0x00);
    GC9A01_WriteByte(0x00);

    GC9A01_WriteCommand(0x36);

#if ORIENTATION == 0
    GC9A01_WriteByte(0x18);
#elif ORIENTATION == 1
    GC9A01_WriteByte(0x28);
#elif ORIENTATION == 2
    GC9A01_WriteByte(0x48);
#else
    GC9A01_WriteByte(0x88);
#endif

    GC9A01_WriteCommand(GC9A01_COLMOD);
    GC9A01_WriteByte(GC9A01_COLMOD_16_BIT);

    GC9A01_WriteCommand(0x90);
    GC9A01_WriteByte(0x08);
    GC9A01_WriteByte(0x08);
    GC9A01_WriteByte(0x08);
    GC9A01_WriteByte(0x08);

    GC9A01_WriteCommand(0xBD);
    GC9A01_WriteByte(0x06);

    GC9A01_WriteCommand(0xBC);
    GC9A01_WriteByte(0x00);

    GC9A01_WriteCommand(0xFF);
    GC9A01_WriteByte(0x60);
    GC9A01_WriteByte(0x01);
    GC9A01_WriteByte(0x04);

    GC9A01_WriteCommand(0xC3);
    GC9A01_WriteByte(0x13);
    GC9A01_WriteCommand(0xC4);
    GC9A01_WriteByte(0x13);

    GC9A01_WriteCommand(0xC9);
    GC9A01_WriteByte(0x22);

    GC9A01_WriteCommand(0xBE);
    GC9A01_WriteByte(0x11);

    GC9A01_WriteCommand(0xE1);
    GC9A01_WriteByte(0x10);
    GC9A01_WriteByte(0x0E);

    GC9A01_WriteCommand(0xDF);
    GC9A01_WriteByte(0x21);
    GC9A01_WriteByte(0x0c);
    GC9A01_WriteByte(0x02);

    GC9A01_WriteCommand(0xF0);
    GC9A01_WriteByte(0x45);
    GC9A01_WriteByte(0x09);
    GC9A01_WriteByte(0x08);
    GC9A01_WriteByte(0x08);
    GC9A01_WriteByte(0x26);
    GC9A01_WriteByte(0x2A);

    GC9A01_WriteCommand(0xF1);
    GC9A01_WriteByte(0x43);
    GC9A01_WriteByte(0x70);
    GC9A01_WriteByte(0x72);
    GC9A01_WriteByte(0x36);
    GC9A01_WriteByte(0x37);
    GC9A01_WriteByte(0x6F);

    GC9A01_WriteCommand(0xF2);
    GC9A01_WriteByte(0x45);
    GC9A01_WriteByte(0x09);
    GC9A01_WriteByte(0x08);
    GC9A01_WriteByte(0x08);
    GC9A01_WriteByte(0x26);
    GC9A01_WriteByte(0x2A);

    GC9A01_WriteCommand(0xF3);
    GC9A01_WriteByte(0x43);
    GC9A01_WriteByte(0x70);
    GC9A01_WriteByte(0x72);
    GC9A01_WriteByte(0x36);
    GC9A01_WriteByte(0x37);
    GC9A01_WriteByte(0x6F);

    GC9A01_WriteCommand(0xED);
    GC9A01_WriteByte(0x1B);
    GC9A01_WriteByte(0x0B);

    GC9A01_WriteCommand(0xAE);
    GC9A01_WriteByte(0x77);
    
    GC9A01_WriteCommand(0xCD);
    GC9A01_WriteByte(0x63);

    GC9A01_WriteCommand(0x70);
    GC9A01_WriteByte(0x07);
    GC9A01_WriteByte(0x07);
    GC9A01_WriteByte(0x04);
    GC9A01_WriteByte(0x0E);
    GC9A01_WriteByte(0x0F);
    GC9A01_WriteByte(0x09);
    GC9A01_WriteByte(0x07);
    GC9A01_WriteByte(0x08);
    GC9A01_WriteByte(0x03);

    GC9A01_WriteCommand(0xE8);
    GC9A01_WriteByte(0x34);

    GC9A01_WriteCommand(0x62);
    GC9A01_WriteByte(0x18);
    GC9A01_WriteByte(0x0D);
    GC9A01_WriteByte(0x71);
    GC9A01_WriteByte(0xED);
    GC9A01_WriteByte(0x70);
    GC9A01_WriteByte(0x70);
    GC9A01_WriteByte(0x18);
    GC9A01_WriteByte(0x0F);
    GC9A01_WriteByte(0x71);
    GC9A01_WriteByte(0xEF);
    GC9A01_WriteByte(0x70);
    GC9A01_WriteByte(0x70);

    GC9A01_WriteCommand(0x63);
    GC9A01_WriteByte(0x18);
    GC9A01_WriteByte(0x11);
    GC9A01_WriteByte(0x71);
    GC9A01_WriteByte(0xF1);
    GC9A01_WriteByte(0x70);
    GC9A01_WriteByte(0x70);
    GC9A01_WriteByte(0x18);
    GC9A01_WriteByte(0x13);
    GC9A01_WriteByte(0x71);
    GC9A01_WriteByte(0xF3);
    GC9A01_WriteByte(0x70);
    GC9A01_WriteByte(0x70);

    GC9A01_WriteCommand(0x64);
    GC9A01_WriteByte(0x28);
    GC9A01_WriteByte(0x29);
    GC9A01_WriteByte(0xF1);
    GC9A01_WriteByte(0x01);
    GC9A01_WriteByte(0xF1);
    GC9A01_WriteByte(0x00);
    GC9A01_WriteByte(0x07);

    GC9A01_WriteCommand(0x66);
    GC9A01_WriteByte(0x3C);
    GC9A01_WriteByte(0x00);
    GC9A01_WriteByte(0xCD);
    GC9A01_WriteByte(0x67);
    GC9A01_WriteByte(0x45);
    GC9A01_WriteByte(0x45);
    GC9A01_WriteByte(0x10);
    GC9A01_WriteByte(0x00);
    GC9A01_WriteByte(0x00);
    GC9A01_WriteByte(0x00);

    GC9A01_WriteCommand(0x67);
    GC9A01_WriteByte(0x00);
    GC9A01_WriteByte(0x3C);
    GC9A01_WriteByte(0x00);
    GC9A01_WriteByte(0x00);
    GC9A01_WriteByte(0x00);
    GC9A01_WriteByte(0x01);
    GC9A01_WriteByte(0x54);
    GC9A01_WriteByte(0x10);
    GC9A01_WriteByte(0x32);
    GC9A01_WriteByte(0x98);

    GC9A01_WriteCommand(0x74);
    GC9A01_WriteByte(0x10);
    GC9A01_WriteByte(0x85);
    GC9A01_WriteByte(0x80);
    GC9A01_WriteByte(0x00);
    GC9A01_WriteByte(0x00);
    GC9A01_WriteByte(0x4E);
    GC9A01_WriteByte(0x00);

    GC9A01_WriteCommand(0x98);
    GC9A01_WriteByte(0x3e);
    GC9A01_WriteByte(0x07);

    GC9A01_WriteCommand(0x35);
    GC9A01_WriteCommand(0x21);

    GC9A01_WriteCommand(0x11);
    HAL_Delay(120);
    GC9A01_WriteCommand(0x29);
    HAL_Delay(20);
}

uint16_t GC9A01_Color565(uint8_t r, uint8_t g, uint8_t b)
{
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void GC9A01_invertDisplay(int i)
{
    GC9A01_WriteCommand((i == 0) ? GC9A01_INVOFF : GC9A01_INVON);
}

// void GC9A01_fillScreen(uint16_t color) {
// 	GC9A01_fillRect(0, 0,  GC9A01_HOR_RES, GC9A01_VER_RES, color);
// }

void GC9A01_SetFrame(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    uint16_t x_start = x0 + GC9A01_XSTART, x_end = x1 + GC9A01_XSTART;
    uint16_t y_start = y0 + GC9A01_YSTART, y_end = y1 + GC9A01_YSTART;

    GC9A01_WriteCommand(GC9A01_CASET);
    GC9A01_WriteByte((x_start >> 8) & 0xFF);
    GC9A01_WriteByte(x_start & 0xFF);
    GC9A01_WriteByte((x_end >> 8) & 0xFF);
    GC9A01_WriteByte(x_end & 0xFF);

    GC9A01_WriteCommand(GC9A01_RASET);
    GC9A01_WriteByte((y_start >> 8) & 0xFF);
    GC9A01_WriteByte(y_start & 0xFF);
    GC9A01_WriteByte((y_end >> 8) & 0xFF);
    GC9A01_WriteByte(y_end & 0xFF);
}
