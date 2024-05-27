#ifndef SSD1306_HANDLER_H_
    #define SSD1306_HANDLER_H_
    
    void init_ssd1306(int SDA_pin, int SCL_pin);
    void send_cmd(uint8_t data[], size_t len);
#endif