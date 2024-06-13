#ifndef SSD1306_HANDLER_H_
    #define SSD1306_HANDLER_H_

    void initialize_SSD1306(uint i2c_sda_pin, uint i2c_scl_pin);
    void write_SDD1306_line(char *string_line);
    void clear_SSD1306_memory();
#endif