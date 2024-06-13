// libs:
#include "stdlib.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "string.h"
// header files:
#include "ssd1306_handler.h"
#include "ssd1306_font.h"

#define PICO_DEFAULT_I2C 1

#define SSD1306_HEIGHT 64
#define SSD1306_WIDTH 128

// Define the size of the display we have attached. This can vary, make sure you
// have the right size defined or the output will look rather odd!
// Code has been tested on 128x32 and 128x64 OLED displays

// slave address (see SSD1306 datasheet):
#define SSD1306_I2C_SLAVE_ADDR _u(0x3C)

// 400 is usual, but often these can be overclocked to improve display response.
#define SSD1306_I2C_CLK 400

// command table (see SSD1306 datasheet):
#define SSD1306_SET_MEM_MODE        _u(0x20)
#define SSD1306_SET_COL_ADDR        _u(0x21)
#define SSD1306_SET_PAGE_ADDR       _u(0x22)
#define SSD1306_SET_HORIZ_SCROLL    _u(0x26)
#define SSD1306_SET_SCROLL          _u(0x2E)

#define SSD1306_SET_DISP_START_LINE _u(0x40)

#define SSD1306_SET_CONTRAST        _u(0x81)
#define SSD1306_SET_CHARGE_PUMP     _u(0x8D)

#define SSD1306_SET_SEG_REMAP       _u(0xA0)
#define SSD1306_SET_ENTIRE_ON       _u(0xA4)
#define SSD1306_SET_ALL_ON          _u(0xA5)
#define SSD1306_SET_NORM_DISP       _u(0xA6)
#define SSD1306_SET_INV_DISP        _u(0xA7)
#define SSD1306_SET_MUX_RATIO       _u(0xA8)
#define SSD1306_SET_DISP            _u(0xAE)
#define SSD1306_SET_COM_OUT_DIR     _u(0xC0)
#define SSD1306_SET_COM_OUT_DIR_FLIP _u(0xC0)

#define SSD1306_SET_DISP_OFFSET     _u(0xD3)
#define SSD1306_SET_DISP_CLK_DIV    _u(0xD5)
#define SSD1306_SET_PRECHARGE       _u(0xD9)
#define SSD1306_SET_COM_PIN_CFG     _u(0xDA)
#define SSD1306_SET_VCOM_DESEL      _u(0xDB)

#define SSD1306_PAGE_HEIGHT         _u(8)
#define SSD1306_NUM_PAGES           (SSD1306_HEIGHT / SSD1306_PAGE_HEIGHT)
#define SSD1306_MEMORY_SIZE         (SSD1306_NUM_PAGES * SSD1306_WIDTH)

#define SSD1306_WRITE_MODE         _u(0xFE)
#define SSD1306_READ_MODE          _u(0xFF)

static void send_command(uint8_t command) {
    // I2C write process expects a control byte followed by data
    // this "data" can be a command or data to follow up a command
    // Co = 1, D/C = 0 => the driver expects a command
    uint8_t command_block[2] = {0x80, command};
    i2c_write_blocking(i2c_default, SSD1306_I2C_SLAVE_ADDR, command_block, count_of(command_block), false);
}

static void send_command_list(uint8_t *command_list, int length) {
    for (int i = 0; i < length; i++) {
        send_command(command_list[i]);
    }
}

static void configure_display() {
    uint8_t commands[] = {
        SSD1306_SET_DISP,               // set display off
        /* memory mapping */
        SSD1306_SET_MEM_MODE,           // set memory address mode 0 = horizontal, 1 = vertical, 2 = page
        0x00,                           // horizontal addressing mode
        /* resolution and layout */
        SSD1306_SET_DISP_START_LINE,    // set display start line to 0
        SSD1306_SET_SEG_REMAP | 0x01,   // set segment re-map, column address 127 is mapped to SEG0
        SSD1306_SET_MUX_RATIO,          // set multiplex ratio
        SSD1306_HEIGHT - 1,             // Display height - 1
        SSD1306_SET_COM_OUT_DIR | 0x08, // set COM (common) output scan direction. Scan from bottom up, COM[N-1] to COM0
        SSD1306_SET_DISP_OFFSET,        // set display offset
        0x00,                           // no offset

        SSD1306_SET_COM_PIN_CFG,        // set COM (common) pins hardware configuration. Board specific magic number. 
                                        // 0x02 Works for 128x32, 0x12 Possibly works for 128x64. Other options 0x22, 0x32
#if ((SSD1306_WIDTH == 128) && (SSD1306_HEIGHT == 32))
        0x02,                           
#elif ((SSD1306_WIDTH == 128) && (SSD1306_HEIGHT == 64))
        0x12,
#else
        0x02,
#endif

        SSD1306_SET_DISP_CLK_DIV,       // set display clock divide ratio
        0x80,                           // div ratio of 1, standard freq
        SSD1306_SET_PRECHARGE,          // set pre-charge period
        0xF1,                           // Vcc internally generated on our board
        SSD1306_SET_VCOM_DESEL,         // set VCOMH deselect level
        0x30,                           // 0.83xVcc
        /* display */
        SSD1306_SET_CONTRAST,           // set contrast control
        0xFF,
        SSD1306_SET_ENTIRE_ON,          // set entire display on to follow RAM content
        SSD1306_SET_NORM_DISP,           // set normal (not inverted) display
        SSD1306_SET_CHARGE_PUMP,        // set charge pump
        0x14,                           // Vcc internally generated on our board
        SSD1306_SET_SCROLL | 0x00,      // deactivate horizontal scrolling if set. This is necessary as memory writes will corrupt if scrolling was enabled
        SSD1306_SET_DISP | 0x01, // turn display on
    };

    send_command_list(commands, count_of(commands));
}

static uint8_t display_memory[SSD1306_MEMORY_SIZE] = {0};

static void render_display() {
    uint8_t transit_array[SSD1306_MEMORY_SIZE + 1];
    transit_array[0] = 0x40;

    memcpy(transit_array+1, display_memory, SSD1306_MEMORY_SIZE);
    i2c_write_blocking(i2c_default, SSD1306_I2C_SLAVE_ADDR, transit_array, SSD1306_MEMORY_SIZE + 1, false);
}

static int get_index_font_symbol(uint8_t character) {
    if (character > '~' || character < '!')
        return 0;
    else
        return (character - 32);
}

static void write_character_display_memory(uint8_t x, uint8_t y, uint8_t character) {
    if(x > SSD1306_WIDTH - FONT_PIXEL_WIDTH) return;
    if(y > SSD1306_HEIGHT - SSD1306_PAGE_HEIGHT) return;

    // For the moment, only write on Y row boundaries (every 8 vertical pixels)
    y = (uint8_t)(y / SSD1306_PAGE_HEIGHT);

    uint8_t index_font_symbol = get_index_font_symbol(character);
    uint16_t index_pixel_horizontal_mode = y * SSD1306_WIDTH + x;

    for (int i = 0; i < FONT_PIXEL_WIDTH; i++) {
        display_memory[index_pixel_horizontal_mode++] = font[index_font_symbol][i];
    }
}

static void write_string_display_memory(uint8_t x, uint8_t y, char *string_line) {
    if(x > SSD1306_WIDTH - FONT_PIXEL_WIDTH) return;
    if(y > SSD1306_HEIGHT - SSD1306_PAGE_HEIGHT) return;

    while (*string_line) {
        write_character_display_memory(x, y, *string_line++);
        x += FONT_PIXEL_WIDTH;
    }
}

void initialize_SSD1306(uint i2c_sda_pin, uint i2c_scl_pin) {
    i2c_init(i2c_default, SSD1306_I2C_CLK * 1000);

    gpio_set_function(i2c_sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(i2c_scl_pin, GPIO_FUNC_I2C);
    gpio_pull_up(i2c_sda_pin);
    gpio_pull_up(i2c_scl_pin);

    configure_display();
    render_display();
}

static uint8_t display_y_position = 0;

void write_SDD1306_line(char *string_line) {
    if (display_y_position == SSD1306_HEIGHT) display_y_position = 0;

    write_string_display_memory(0, display_y_position, string_line);
    render_display();

    display_y_position += SSD1306_PAGE_HEIGHT;
}

void clear_SSD1306_memory() {
    display_y_position = 0;

    memset(display_memory, 0x00, SSD1306_MEMORY_SIZE);
    render_display();
}