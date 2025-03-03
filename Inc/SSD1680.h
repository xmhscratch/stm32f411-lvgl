#ifndef GFX_SSD1680_H
#define GFX_SSD1680_H

// #include "EPD.h"

#define SSD1680_DRIVER_CONTROL 0x01
#define SSD1680_GATE_VOLTAGE 0x03
#define SSD1680_SOURCE_VOLTAGE 0x04
#define SSD1680_PROGOTP_INITIAL 0x08
#define SSD1680_PROGREG_INITIAL 0x09
#define SSD1680_READREG_INITIAL 0x0A
#define SSD1680_BOOST_SOFTSTART 0x0C
#define SSD1680_DEEP_SLEEP 0x10
#define SSD1680_DATA_MODE 0x11
#define SSD1680_SW_RESET 0x12
#define SSD1680_TEMP_CONTROL 0x18
#define SSD1680_TEMP_WRITE 0x1A
#define SSD1680_MASTER_ACTIVATE 0x20
#define SSD1680_DISP_CTRL1 0x21
#define SSD1680_DISP_CTRL2 0x22
#define SSD1680_WRITE_RAM1 0x24
#define SSD1680_WRITE_RAM2 0x26
#define SSD1680_WRITE_VCOM 0x2C
#define SSD1680_READ_OTP 0x2D
#define SSD1680_READ_STATUS 0x2F
#define SSD1680_WRITE_LUT 0x32
#define SSD1680_WRITE_BORDER 0x3C
#define SSD1680_SET_RAMXPOS 0x44
#define SSD1680_SET_RAMYPOS 0x45
#define SSD1680_SET_RAMXCOUNT 0x4E
#define SSD1680_SET_RAMYCOUNT 0x4F

// Adafruit_SSD1680(int width, int height, int16_t SID, int16_t SCLK, int16_t DC,
//                    int16_t RST, int16_t CS, int16_t SRCS, int16_t MISO,
//                    int16_t BUSY = -1);

// Adafruit_SSD1680(int width, int height, int16_t DC, int16_t RST, int16_t CS,
//                 int16_t SRCS, int16_t BUSY = -1, SPIClass *spi = &SPI);

// void begin(bool reset = true);
// void powerUp();
// void update();
// void powerDown();

// uint8_t writeRAMCommand(uint8_t index);
// void setRAMAddress(uint16_t x, uint16_t y);
// void busy_wait();

// int8_t _xram_offset = 1;

#endif
