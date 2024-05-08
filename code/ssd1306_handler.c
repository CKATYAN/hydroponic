#include "stdlib.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "string.h"

#include "ssd1306_handler.h"

const uint8_t OLED_ID = 0x3C;

uint8_t DISPLAY_INIT[25] = {0xAE, 0x20, 0x00, 0x40, 0xA1, 0xA8, 0x3F,
                            0xC8, 0xD3, 0x00, 0xDA, 0x12, 0xD5, 0x80,
                            0xD9, 0xF1, 0xDB, 0x30, 0x81, 0xFF, 0xA4,
                            0xA6, 0x8D, 0x14, 0xAF};

void send_cmd(uint8_t data[], size_t len) {
    uint8_t *outdata = malloc(len + 1);
    outdata[0] = 0x00;
    memcpy(outdata + 1, data, len);
    i2c_write_blocking(i2c_default, OLED_ID, outdata, len + 1, false);
    free(outdata);
}

void init_ssd1306(int SDA_pin, int SCL_pin) {
    i2c_init(i2c_default, 100 * 1000);

    gpio_set_function(SDA_pin, GPIO_FUNC_I2C);
    gpio_set_function(SCL_pin, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_pin);
    gpio_pull_up(SCL_pin);

    send_cmd(DISPLAY_INIT, sizeof(DISPLAY_INIT) / sizeof(uint8_t));
}
    