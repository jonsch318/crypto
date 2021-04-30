#include "../include/console.h"

#ifdef __unix__
char s_color[15] = "";
//TODO

void console_clear(void)
{
    printf("\e[1;1H\e[2J");
}

void console_set_color(int f, int b)
{
    int foreground = f;
    int background = b + 10;
    sprintf(s_color, "\x1b[%d;%dm", background, foreground);
}

void console_reset_color(void)
{
    sprintf(s_color, "\x1b[%d;%dm", 0, 37);
}

#elif defined(_WIN32) || defined(_WIN64)

#include <stdint.h>
#include <windows.h>

#define COL(f, b) ((uint8_t)((b << 4) | f))

uint8_t color_get(int r, int g, int b)
{
    return (((r != 0) * 0b0100) | ((g != 0) * 0b0010)) | ((b != 0) * 0b0001);
}

void console_set_color(int f, int b)
{
    HANDLE console_handle;
    console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_handle, COL(f, b));
}

void console_reset_color(void)
{
    HANDLE console_handle;
    console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_handle, 0b00001111);
}

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