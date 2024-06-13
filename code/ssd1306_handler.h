#ifndef SSD1306_HANDLER_H_
    #define SSD1306_HANDLER_H_

    void SSD1306_initialize(uint i2c_sda_pin, uint i2c_scl_pin);
    void SDD1306_write_line(char *string_line);
    void SSD1306_clear_memory();
#endif