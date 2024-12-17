# GC9A01 TFT display

[LVGL](https://github.com/lvgl/lvgl) with DMA on STM32F411.

## Setup

```bash
# generate code
pip install stm32pio
stm32pio generate

# gc9a01 pin config
| Signal        | Pin     |
| ------------- |:-------:|
| DC            | PB0     |
| RST           | PB1     |
| CS            | PA4     |
| SCL           | PA5     |
| SDA           | PA7     |
| GND           | GND     |
| VCC           | 3V3     |
