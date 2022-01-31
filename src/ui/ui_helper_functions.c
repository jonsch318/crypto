#include "ui/ui_helper_functions.h"
#include "terminal.h"
#include "helper_functions.h"
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#ifdef USE_GMP
#include <gmp.h>
#endif

/**
 * @brief The "UI" for the primality test
 * @return (void)
 */
void m_is_prime()
{
    uint32_t p = 0;
    terminal_clear();
    terminal_set_color(WHITE, BLACK);
    printf("Primality test:\n");
    printf("Please enter a number: ");
    terminal_set_color(LIGHT_WHITE, BLACK);
    scanf("%" PRIu32 "", &p);
    if (is_prime(p))
    {
        terminal_clear();
        terminal_set_color(LIGHT_GREEN, BLACK);
        printf("%" PRIu32 " is a prime number.\n", p);
    }
    else
    {
        terminal_clear();
        terminal_set_color(LIGHT_RED, BLACK);
        printf("%" PRIu32 " is not a prime number.\n", p);
    }
    terminal_reset_color();
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
void m_prime_get()
{
    int i = 0;
#if !USE_GMP
    int n = 0;
    uint32_t p = 0;
#elif USE_GMP
    mpz_t p;
    int tmp = 0;
    mp_bitcnt_t n = 1;
    mpz_init(p);
#endif
    terminal_clear();
    terminal_set_color(WHITE, BLACK);
    printf("Random prime number generator:\n");
    printf("Please enter the amount and size of numbers to be generated: ");
    terminal_set_color(LIGHT_WHITE, BLACK);
#if !USE_GMP
    scanf("%d %d", &i, &n);
#elif USE_GMP
    scanf("%d %d", &i, &tmp);
    n = (mp_bitcnt_t)tmp;
#endif
    terminal_clear();
    while (i)
    {
        terminal_set_color((i % 2) * WHITE + (!(i % 2)) * GRAY, BLACK);
#if !USE_GMP
        p = prime_get(n);
        printf("%d: %" PRIu32 "\n", i, p);
#elif USE_GMP
        prime_gmp_get(n, &p);
        gmp_printf("%d: %Zd\n", i, p);
#endif
        i--;
    }
#if USE_GMP
    mpz_clear(p);
#endif
    terminal_reset_color();
    getchar();
    printf("Press enter to return...");
    while (getchar() != '\n')
    {
    }
}