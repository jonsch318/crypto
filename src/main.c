#include "../include/RSA.h"
#include "../include/console.h"
#include "../include/helper_functions.h"
#include <stdio.h>

int main()
{

#if defined(_WIN32) || defined(_WIN64)
    console_clear();
    console_set_color(WHITE, BLACK);
    printf("RSA:\n");
    printf("Please enter two prime numbers");
    console_set_color(GRAY, BLACK);
    printf(" (prime_1 prime_2):\n");
    console_reset_color();
    uint32_t p = 0;
    uint32_t q = 0;
    uint32_t N = 0;
    uint32_t e = 0;
    uint32_t d = 0;
    do
    {
        scanf("%lu %lu", &p, &q);
        console_clear();

    } while (is_prime(p) && is_prime(q));
    RSA_get(p, q, &N, &e, &d);
    printf("p: %lu\nq: %lu\nN: %lu\ne: %lu\nd: %lu\n", p, q, N, e, d);
    console_set_color(GREEN, BLACK);
    printf("Public key: {N: %lu, e: %lu}\n", N, e);
    console_set_color(RED, BLACK);
    printf("Private key: {N: %lu, d: %lu}\n", N, d);
    console_reset_color();

#elif defined(__unix__)
    printf("RSA:\n");
    printf("Please enter two prime numbers (prime_1 prime_2):\n");
    uint32_t p = 0;
    uint32_t q = 0;
    uint32_t N = 0;
    uint32_t e = 0;
    uint32_t d = 0;
    do
    {
        scanf("%lu %lu", &p, &q);
        console_clear();

    } while (!is_prime(p) && !is_prime(q));
    RSA_get(p, q, &N, &e, &d);
    printf("p: %lu\nq: %lu\nN: %lu\ne: %lu\nd: %lu\n", p, q, N, e, d);
    printf(GREEN "Public key: {N: %lu, e: %lu}\n" RESET, N, e);
    printf(RED "Private key: {N: %lu, d: %lu}\n" RESET, N, d);
#endif
    return 0;
}