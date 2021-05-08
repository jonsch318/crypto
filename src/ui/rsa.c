#include "../include/ui/rsa.h"
#include "../../include/console.h"
#include "../../include/RSA.h"
#include "../../include/helper_functions.h"
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

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
        scanf("%" PRIu32 " %" PRIu32 "", &p, &q);
        console_clear();

    } while (!is_prime(p) || !is_prime(q));
    RSA_get(p, q, &N, &e, &d);
    printf("p: %" PRIu32 "\nq: %" PRIu32 "\nN: %" PRIu32 "\ne: %" PRIu32 "\nd: %" PRIu32 "\n", p, q, N, e, d);
    console_set_color(GREEN, BLACK);
    printf("Public key: {N: %" PRIu32 ", e: %" PRIu32 "}\n", N, e);
    console_set_color(RED, BLACK);
    printf("Private key: {N: %" PRIu32 ", d: %" PRIu32 "}\n", N, d);
    console_reset_color();
    getchar();
    printf("Press enter to return...");
    while (getchar() != '\n')
    {
    }
}

/**
 * @brief The "UI" for encrypting with the RSA algorithm
 * @return (void)
 */
void m_rsa_encrypt()
{
    uint32_t n = 0;
    uint32_t e = 0;
    char str[250];
    char *encrypted = NULL;
    console_clear();
    console_set_color(WHITE, BLACK);
    printf("RSA -> encrypt:\n");
    printf("Please enter the public key");
    console_set_color(GRAY, BLACK);
    printf(" (N e):\n");
    console_reset_color();
    scanf("%" PRIu32 " %" PRIu32 "", &n, &e);
    console_set_color(WHITE, BLACK);
    printf("Please enter the text to be encrypted (max. 250): ");
    console_reset_color();
    getchar();
    scanf("%[^\n]s", str);
    encrypted = RSA_encrypt_string(str, n, e, encrypted);
    console_clear();
    console_set_color(LIGHT_WHITE, BLACK);
    printf("Input:\n");
    console_set_color(WHITE, BLACK);
    printf("%s\n", str);
    console_set_color(LIGHT_WHITE, BLACK);
    printf("Output:\n");
    console_set_color(WHITE, BLACK);
    printf("%s\n\n", encrypted);
    free(encrypted);
    console_reset_color();
    getchar();
    printf("Press enter to return...");
    while (getchar() != '\n')
    {
    }
}