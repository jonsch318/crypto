#include "../include/TUI/helper_functions.h"
#include "../../include/console.h"
#include "../../include/helper_functions.h"
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

/**
 * @brief The "UI" for the primality test
 * @return (void)
 */
void m_is_prime()
{
    uint32_t p = 0;
    console_clear();
    console_set_color(WHITE, BLACK);
    printf("Primality test:\n");
    printf("Please enter a number: ");
    console_set_color(LIGHT_WHITE, BLACK);
    scanf("%" PRIu32 "", &p);
    if (is_prime(p))
    {
        console_clear();
        console_set_color(LIGHT_GREEN, BLACK);
        printf("%" PRIu32 " is a prime number.\n", p);
    }
    else
    {
        console_clear();
        console_set_color(LIGHT_RED, BLACK);
        printf("%" PRIu32 " is not a prime number.\n", p);
    }
    console_reset_color();
    getchar();
    printf("Press enter to return...");
    while (getchar() != '\n')
    {
    }
}

/**
 * @brief The "UI" for the random prime number generator
 * @return (void)
 */
void m_get_prime()
{
    uint32_t p = 0;
    int i = 0;
    console_clear();
    console_set_color(WHITE, BLACK);
    printf("Random prime number generator:\n");
    printf("Please enter the amount of numbers to be generated: ");
    console_set_color(LIGHT_WHITE, BLACK);
    scanf("%d", &i);
    console_clear();
    while (i)
    {
        p = get_prime();
        console_set_color((i % 2) * WHITE + (!(i % 2)) * GRAY, BLACK);
        printf("%d: %" PRIu32 "\n", i, p);
        i--;
    }
    console_reset_color();
    getchar();
    printf("Press enter to return...");
    while (getchar() != '\n')
    {
    }
}