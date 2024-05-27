#include "stdlib.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "string.h"

#include "ssd1306_handler.h"

const uint8_t SSD1306_SLAVE_ADDR = 0x3C;

uint8_t DISPLAY_INIT[19] = {
    0xAE, // turn display off
    0xA8, 0x3F, // set 128x64
    0xD3, 0x00, // no offset
    0x20, 0x00, // set horiz addr mode
    0x40, // start line 0
    0xA0,
    0xC0,
    0x81, 0x7F, // set contrast
    0xA4, // disable entire display on
    0xA6, // set normal display
    0xD5, 0x80, // set osc freq
    0x8D, 0x14, // 
    0xAF, // turn display on
};

void send_cmd(uint8_t data[], size_t length) {
    uint8_t *outdata = malloc(length + 1);
    outdata[0] = 0x00;
    memcpy(outdata + 1, data, length);

    i2c_write_blocking(i2c1, SSD1306_SLAVE_ADDR, outdata, length + 1, false);
    free(outdata);
}

void init_ssd1306(int SDA_pin, int SCL_pin) {
    i2c_init(i2c1, 400 * 1000);

    gpio_set_function(SDA_pin, GPIO_FUNC_I2C);
    gpio_set_function(SCL_pin, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_pin);
    gpio_pull_up(SCL_pin);

    send_cmd(DISPLAY_INIT, sizeof(DISPLAY_INIT) / sizeof(uint8_t));
}


    