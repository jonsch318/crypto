#include "../include/menu.h"
#include "../include/console.h"
#include "../include/RSA.h"
#include "../include/helper_functions.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#endif

extern char *s_color;

void m_draw(void);
void m_loop(void);
void m_rsa(void);
void m_exit(void);

struct entry
{
    char title[15]; //Text written on the screen
    int foreground; //foreground color
    int background; //background color
    int s_foreground; //foreground color -> selected
    int s_background; //background color -> selected
    void (*run)(void); //Function to be executed when selected
};

struct menu
{
    struct entry entrys[2];
    //I don't think there will be more than 255 entries -> uint8_t 0-255
    uint8_t num_entrys; //Number of entrys
    uint8_t selected; //Index of selected entry
} m;

void m_main()
{
    struct entry e_rsa = {"RSA", WHITE, BLACK, BLACK, WHITE, &m_rsa};
    struct entry e_exit = {"EXIT", WHITE, BLACK, BLACK, WHITE, &m_exit};
    m.entrys[0] = e_rsa;
    m.entrys[1] = e_exit;
    m.num_entrys = 2;
    m.selected = 0;
    m_loop();
}

void m_draw()
{
    console_clear();
    printf("\n");
    for (uint8_t i = 0; i < m.num_entrys; i++)
    {
        if (m.selected == i)
        {
            printf(" -> ");
            console_set_color(m.entrys[(int)i].s_foreground, m.entrys[(int)i].s_background);
        }
        else
        {
            printf("    ");
            console_set_color(m.entrys[(int)i].foreground, m.entrys[(int)i].background);
        }
        printf("%s\n", m.entrys[(int)i].title);
        console_reset_color();
    }
}

void m_loop()
{
    int ch;
    int key;
    for (;;)
    {
        key = -1;
        m_draw();
#if defined(_WIN32) || defined(_WIN64)
        ch = getch();
        switch (ch)
        {
        case 0xE0:
            ch = getch();
            switch (ch)
            {
            case 0x4B: //LEFT
                key = 0;
                break;
                key = 1;
            case 0x48: //UP
                key = 2;
                break;
            case 0x4D: //RIGHT
                key = 3;
                break;
            case 0x50: //DOWN
                key = 4;
                break;
            }
            break;
        case 0x0D: //RETURN
        case 0x20: //SPACE
            key = 5;
            break;
        case 0x1B: //ESCAPE
            key = 6;
            break;
        }
#elif defined(__unix__)
        //getchar does not return codes for the arrow keys
        ch = getchar();
        switch (ch)
        {
        case 0xE0:
            ch = getchar();
            switch (ch)
            {
            case 0x4B: //LEFT
                key = 0;
                break;
                key = 1;
            case 0x48: //UP
                key = 2;
                break;
            case 0x4D: //RIGHT
                key = 3;
                break;
            case 0x50: //DOWN
                key = 4;
                break;
            }
            break;
        case 0x0D: //RETURN
        case 0x20: //SPACE
            key = 5;
            break;
        case 0x1B: //ESCAPE
            key = 6;
            break;
        }
#endif
        switch (key)
        {
        case 0:
            break;
        case 1:
            break;
        case 2:
            m.selected--;
            break;
        case 3:
            break;
        case 4:
            m.selected++;
            break;
        case 5:
            m.entrys[m.selected].run();
            break;
        case 6:
            exit(0);
            break;
        }
        m.selected = (m.selected > 0) * (m.selected % m.num_entrys);
    }
}

void m_rsa()
{
    console_clear();
    console_set_color(WHITE, BLACK);
    c_printf("RSA:\n");
    uint32_t p = 0;
    uint32_t q = 0;
    uint32_t N = 0;
    uint32_t e = 0;
    uint32_t d = 0;
    do
    {
        c_printf("Please enter two prime numbers");
        console_set_color(GRAY, BLACK);
        c_printf(" (prime_1 prime_2):\n");
        console_reset_color();
        scanf("%u %u", &p, &q);
        console_clear();

    } while (is_prime(p) != 0 || is_prime(q) != 0);
    RSA_get(p, q, &N, &e, &d);
    c_printf("p: %u\nq: %u\nN: %u\ne: %u\nd: %u\n", p, q, N, e, d);
    console_set_color(GREEN, BLACK);
    c_printf("Public key: {N: %u, e: %u}\n", N, e);
    console_set_color(RED, BLACK);
    c_printf("Private key: {N: %u, d: %u}\n", N, d);
    console_reset_color();
    getchar();
    printf("Press enter to return...");
    while (getchar() != '\n')
    {
        //flush input buffer
    }
}

void m_exit()
{
    console_clear();
    exit(0);
}