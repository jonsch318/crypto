#include "../include/console.h"

#ifdef __unix__
/**
 * @brief Clears the console
 * @return (void)
 */
void console_clear(void)
{
    printf("\e[1;1H\e[2J");
}
/**
 * @brief Sets the color of the console
 * 
 * @param f Foreground
 * @param b Background
 * @return (void)
 */
void console_set_color(int f, int b)
{
    int foreground = f;
    int background = b + 10;
    printf("\x1b[%d;%dm", background, foreground);
}

/**
 * @brief Resets the colors to black and white
 * @return (void)
 */
void console_reset_color(void)
{
    printf("\x1b[0;37m");
}
#elif defined(_WIN32) || defined(_WIN64)

#include <stdint.h>
#include <windows.h>
/**
 * @brief generates a color from a given foreground and background color
 * 
 */
#define COL(f, b) ((uint8_t)((b << 4) | f))

/**
 * @brief generates a color from r,g and b
 * 
 * @param r activate the red bit
 * @param g activate the green bit
 * @param b activate the blue bit
 * @return uint8_t returns a colour in the form of 0b0rgb
 */
uint8_t color_get(int r, int g, int b)
{
    return (((r != 0) * 0b0100) | ((g != 0) * 0b0010)) | ((b != 0) * 0b0001);
}

/**
 * @brief sets the color of the console
 * @param f the foreground color
 * @param b the background color
 * @return (void)
 */
void console_set_color(int f, int b)
{
    HANDLE console_handle;
    console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_handle, COL(f, b));
}

/**
 * @brief resets the color of the console to black and white
 * @return (void)
 */
void console_reset_color(void)
{
    HANDLE console_handle;
    console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_handle, 0b00001111);
}

/**
 * @brief clears the console
 * @return (void)
 */
void console_clear(void)
{

    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);

    if (console_handle == INVALID_HANDLE_VALUE)
    {
        return;
    }

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer;
    DWORD count;
    DWORD cellCount;
    COORD start_coords = {0, 0};

    if (!GetConsoleScreenBufferInfo(console_handle, &screen_buffer))
    {
        return;
    }

    cellCount = screen_buffer.dwSize.X * screen_buffer.dwSize.Y;

    if (!FillConsoleOutputCharacter(console_handle, (TCHAR)' ', cellCount, start_coords, &count))
    {
        return;
    }

    if (!FillConsoleOutputAttribute(console_handle, screen_buffer.wAttributes, cellCount, start_coords, &count))
    {
        return;
    }

    SetConsoleCursorPosition(console_handle, start_coords);
}

#endif