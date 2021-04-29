#ifndef CONSOLE_H
#define CONSOLE_H

void console_clear();

#if defined(_WIN32) || defined(_WIN64)

void console_reset_color();

void console_set_color(int f, int b);

enum color
{
    BLACK = 0b0000,         //0x00,
    BLUE = 0b0001,          //0x01,
    GREEN = 0b0010,         //0x02,
    CYAN = 0b0011,          //0x03,
    RED = 0b0100,           //0x04,
    MAGENTA = 0b0101,       //0x05,
    YELLOW = 0b0110,        //0x06,
    WHITE = 0b0111,         //0x07,
    GRAY = 0b1000,          //0x08,
    LIGHT_BLUE = 0b1001,    //0x09,
    LIGHT_GREEN = 0b1010,   //0x0A,
    LIGHT_CYAN = 0b1011,    //0x0B,
    LIGHT_RED = 0b1100,     //0x0C,
    LIGHT_MAGENTA = 0b1101, //0x0D,
    LIGHT_YELLOW = 0b1110,  //0x0E,
    BRIGHT_WHITE = 0b1111   //0x0F
};

#elif defined(__unix__)
//usage: printf(RED "red text" RESET)
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"
#endif

#endif // CONSOLE_H
