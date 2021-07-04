#include "../../include/ui/ciphers/ui_rsa.h"
#include "../../../include/console.h"
#include "../../../include/ciphers/rsa.h"
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
#if !RSA_USE_GMP
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
#elif RSA_USE_GMP
    mpz_t p;
    mpz_t q;
    mpz_t N;
    mpz_t e;
    mpz_t d;
    mpz_init(p);
    mpz_init(q);
    mpz_init(N);
    mpz_init(e);
    mpz_init(d);
    do
    {
        printf("Please enter two prime numbers");
        console_set_color(GRAY, BLACK);
        printf(" (prime_1 prime_2):\n");
        console_reset_color();
        gmp_scanf("%Zd %Zd", &p, &q);
        console_clear();

    } while (!mpz_probab_prime_p(p, 25) || !mpz_probab_prime_p(q, 25));
    RSA_gmp_get(p, q, &N, &e, &d);
    gmp_printf("p: %Zd\nq: %Zd\nN: %Zd\ne: %Zd\nd: %Zd\n", p, q, N, e, d);
    console_set_color(GREEN, BLACK);
    gmp_printf("Public key:\n{\n\tN: %Zd,\n\te: %Zd\n}\n", N, e);
    console_set_color(RED, BLACK);
    gmp_printf("Private key:\n{\n\tN: %Zd,\n\td: %Zd\n}\n", N, d);
    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(N);
    mpz_clear(e);
    mpz_clear(d);
#endif
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
#if !RSA_USE_GMP
    uint32_t n = 0;
    uint32_t e = 0;
#elif RSA_USE_GMP
    mpz_t n;
    mpz_t e;
    mpz_init(n);
    mpz_init(e);
#endif
    char str[250];
    char *encrypted = NULL;
    console_clear();
    console_set_color(WHITE, BLACK);
    printf("RSA -> encrypt:\n");
    printf("Please enter the public key");
    console_set_color(GRAY, BLACK);
    printf(" (N e):\n");
    console_reset_color();
#if !RSA_USE_GMP
    scanf("%" PRIu32 " %" PRIu32 "", &n, &e);
#elif RSA_USE_GMP
    gmp_scanf("%Zd %Zd", &n, &e);
#endif
    console_set_color(WHITE, BLACK);
    printf("Please enter the text to be encrypted (max. 250): ");
    console_reset_color();
    getchar();
    scanf("%[^\n]s", str);
#if !RSA_USE_GMP
    encrypted = RSA_encrypt_string(str, n, e, encrypted);
#elif RSA_USE_GMP
    encrypted = RSA_gmp_encrypt_string(str, n, e, encrypted);
    mpz_clear(n);
    mpz_clear(e);
#endif
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