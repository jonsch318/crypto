#include "../include/menu.h"
#include "../include/console.h"
#include "../include/RSA.h"
#include "../include/helper_functions.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#elif defined(__unix__)
#include <termios.h>
#include <sys/ioctl.h>
#endif

extern char *s_color;

void m_draw(void);
void m_loop(void);
void m_rsa(void);
void m_is_prime(void);
void m_exit(void);

struct entry
{
    char title[25];    //Text written on the screen
    int foreground;    //foreground color
    int background;    //background color
    int s_foreground;  //foreground color -> selected
    int s_background;  //background color -> selected
    void (*run)(void); //Function to be executed when selected
};

struct menu
{
    struct entry entrys[3];
    //I don't think there will be more than 255 entries -> uint8_t 0-255
    uint8_t num_entrys; //Number of entrys
    uint8_t selected;   //Index of selected entry
} m;

void m_main()
{
    struct entry e_rsa = {"RSA", WHITE, BLACK, BLACK, WHITE, &m_rsa};
    struct entry e_is_prime = {"Primality test", WHITE, BLACK, BLACK, WHITE, &m_is_prime};
    struct entry e_exit = {"EXIT", WHITE, BLACK, BLACK, WHITE, &m_exit};
    m.entrys[0] = e_rsa;
    m.entrys[1] = e_is_prime;
    m.entrys[2] = e_exit;
    m.num_entrys = 3;
    m.selected = 0;
    m_loop();
}

/**
 * @brief Writes the menu and the entries to the console
 * @return (void)
 */
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

/**
 * @brief The main loop of the program
 * @return (void)
 */
void m_loop()
{
    int ch;
    int key;
    for (;;)
    {
        key = -1;
        m_draw();
#ifdef __unix__
        struct termios term, term_old;
        tcgetattr(0, &term_old);
        tcgetattr(0, &term);
        term.c_lflag &= ~ICANON;
        term.c_lflag &= ~ECHO;
        tcsetattr(0, TCSANOW, &term);
        setbuf(stdin, NULL); //Deactivate buffer
        ch = getchar();
        switch (ch)
        {
        case 0x1B:;
            int bytes;
            ioctl(0, FIONREAD, &bytes);
            if (bytes != 0)
            {
                getchar();
                ch = getchar();
                switch (ch)
                {
                case 0x44: //LEFT
                    key = 0;
                    break;
                    key = 1;
                case 0x41: //UP
                    key = 2;
                    break;
                case 0x43: //RIGHT
                    key = 3;
                    break;
                case 0x42: //DOWN
                    key = 4;
                    break;
                }
            }
            else
            {
                key = 6; //ESCAPE
            }
            break;
        case 0x0A: //RETURN
        case 0x20: //SPACE
            key = 5;
            break;
        }
        tcsetattr(0, TCSANOW, &term_old);
#elif defined(_WIN32) || defined(_WIN64)
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

/**
 * @brief The " UI " for the RSA demo
 * @return (void)
 */
void m_rsa()
{
    console_clear();
    console_set_color(WHITE, BLACK);
    printf("RSA:\n");
    uint32_t p = 0;
    uint32_t q = 0;
    uint32_t N = 0;
    uint32_t e = 0;
    uint32_t d = 0;
    do
    {
        printf("Please enter two prime numbers");
        console_set_color(GRAY, BLACK);
        printf(" (prime_1 prime_2):\n");
        console_reset_color();
        scanf("%u %u", &p, &q);
        console_clear();

    } while (!is_prime(p) || !is_prime(q));
    RSA_get(p, q, &N, &e, &d);
    printf("p: %u\nq: %u\nN: %u\ne: %u\nd: %u\n", p, q, N, e, d);
    console_set_color(GREEN, BLACK);
    printf("Public key: {N: %u, e: %u}\n", N, e);
    console_set_color(RED, BLACK);
    printf("Private key: {N: %u, d: %u}\n", N, d);
    console_reset_color();
    getchar();
    printf("Press enter to return...");
    while (getchar() != '\n')
    {
    }
}

void m_is_prime()
{
    uint32_t p = 0;
    console_clear();
    console_set_color(WHITE, BLACK);
    printf("Primality test:\n");
    printf("Please enter a number: ");
    console_set_color(LIGHT_WHITE, BLACK);
    scanf("%u", &p);
    if (is_prime(p))
    {
        console_clear();
        console_set_color(LIGHT_GREEN, BLACK);
        printf("%u is a prime number.\n", p);
    }
    else
    {
        console_clear();
        console_set_color(LIGHT_RED, BLACK);
        printf("%u is not a prime number.\n", p);
    }
    console_reset_color();
    getchar();
    printf("Press enter to return...");
    while (getchar() != '\n')
    {
    }
}

/**
 * @brief clears the console and stops the program
 * @return (void)
 */
void m_exit()
{
    console_clear();
    exit(0);
}