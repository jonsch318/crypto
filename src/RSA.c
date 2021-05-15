/**
 * @file RSA.c
 * @date 2021-05-07
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <gmp.h>
#include "../include/RSA.h"

static uint32_t rsa_encrypt(uint32_t c, uint32_t n, uint32_t e);
static void rsa_gmp_encrypt(const mpz_t c, const mpz_t n, const mpz_t e, mpz_t *out);
static uint32_t rsa_decrypt(uint32_t m, uint32_t n, uint32_t d);
static void rsa_gmp_decrypt(const mpz_t m, const mpz_t n, const mpz_t d, mpz_t *out);
static uint32_t rsa_pow(uint32_t a, uint32_t b);
static uint32_t rsa_mod(uint32_t a, uint32_t b);
static uint32_t mod_pow(uint32_t b, uint32_t e, uint32_t m);

void RSA_get(uint32_t p, uint32_t q, uint32_t *ret_N, uint32_t *ret_e, uint32_t *ret_d)
{
    uint32_t N;
    uint32_t r;
    uint32_t e;
    uint32_t i;
    N = p * q;
    r = (p - 1) * (q - 1);
    e = 1;
    while ((r % e) == 0)
    {
        e++;
    }
    i = 1;
    while ((i * r + 1) % e != 0)
    {
        i++;
    }
    *ret_N = N;
    *ret_d = (i * r + 1) / e;
    *ret_e = e;
#ifdef DEBUG_RSA
    printf("\nN:\n----------------------------------\n| N = p*q -> %" PRIu32 "*%" PRIu32 " = %" PRIu32 "\n\n", p, q, *ret_N);
    printf("r:\n----------------------------------\n| r = (p-1)*(q-1) -> (%" PRIu32 "-1)*(%" PRIu32 "-1) = %" PRIu32 "\n\n", p, q, r);
    printf("e:\n----------------------------------\n| r mod e != 0 -> %" PRIu32 " mod %" PRIu32 " = %" PRIu32 "\n\n", r, *ret_e, (r % (*ret_e)));
    printf("d:\n----------------------------------\n| (e*d) mod r = 1 -> (%" PRIu32 "*%" PRIu32 ") mod %" PRIu32 " = 1\n\n\n", *ret_e, *ret_d, r);
    printf("----------------------------------\n- p: %" PRIu32 "\n- q: %" PRIu32 "\n- N: %" PRIu32 "\n- r: %" PRIu32 "\n- e: %" PRIu32 "\n- d: %" PRIu32 "\n", p, q, *ret_N, r, *ret_e, *ret_d);
    printf("----------------------------------\npublic: (N: %" PRIu32 ", e: %" PRIu32 ")\nprivate: (N: %" PRIu32 ", d: %" PRIu32 ")\n", *ret_N, *ret_e, *ret_N, *ret_d);
#endif // DEBUG_RSA
}

void RSA_gmp_get(const mpz_t p, const mpz_t q, mpz_t *ret_N, mpz_t *ret_e, mpz_t *ret_d)
{
    mpz_t N;
    mpz_t r;
    mpz_t e;
    mpz_t i;
    mpz_t p_1;
    mpz_t q_1;
    mpz_t tmp;
    mpz_t mod_tmp;

    //Init
    mpz_init(N);
    mpz_init(r);
    mpz_init(e);
    mpz_init_set_ui(i, 1);
    mpz_init(p_1);
    mpz_init(q_1);
    mpz_init_set_ui(tmp, 1);
    mpz_init(mod_tmp);

    //Compute N
    mpz_mul(N, p, q);
    mpz_set(*ret_N, N);

    //Compute r
    mpz_sub_ui(p_1, p, 1);
    mpz_sub_ui(q_1, q, 1);
    mpz_mul(r, p_1, q_1);
    mpz_clear(p_1);
    mpz_clear(q_1);

    //Compute e
    do
    {
        mpz_add_ui(e, e, 1);
        mpz_mod(tmp, r, e);
    } while (mpz_cmp_ui(tmp, 0) == 0);
    mpz_set(*ret_e, e);

    //Compute d
    do
    {
        mpz_add_ui(i, i, 1);
        mpz_mul(mod_tmp, i, r);
        mpz_add_ui(mod_tmp, mod_tmp, 1);
        mpz_mod(mod_tmp, mod_tmp, e);
    } while (mpz_cmp_ui(mod_tmp, 0) != 0);
    mpz_mul(mod_tmp, i, r);
    mpz_add_ui(*ret_d, mod_tmp, 1);
    mpz_div(*ret_d, *ret_d, e);

    mpz_clear(tmp);
    mpz_clear(mod_tmp);
    mpz_clear(N);
    mpz_clear(r);
    mpz_clear(e);
    mpz_clear(i);
}

char *RSA_encrypt_string(const char *in, uint32_t n, uint32_t e, char *out)
{
    FILE *f = tmpfile();
    for (int i = 0; in[i] != '\0'; i++)
    {
        if (in[i] == '\n')
        {
            fprintf(f, "\n");
        }
        else
        {
            uint32_t c = rsa_encrypt((uint32_t)in[i], n, e);
            fprintf(f, "%04" PRIX32 " ", c);
        }
    }
    fseek(f, 0, SEEK_END);
    size_t size = (size_t)ftell(f);
    fseek(f, 0, SEEK_SET);
    out = (char *)malloc(1 + size * sizeof(char));
    fread(out, 1, size, f);
    out[size] = '\0';
    fclose(f);
    return out;
}

char *RSA_gmp_encrypt_string(const char *in, const mpz_t n, const mpz_t e, char *out)
{
    FILE *f = tmpfile();
    mpz_t c;
    mpz_init(c);
    for (int i = 0; in[i] != '\0'; i++)
    {
        if (in[i] == '\n')
        {
            fprintf(f, "\n");
        }
        else
        {
            mpz_set_ui(c, (unsigned long)in[i]);
            rsa_gmp_encrypt(c, n, e, &c);
            gmp_fprintf(f, "%04ZX ", c);
        }
    }
    mpz_clear(c);
    fseek(f, 0, SEEK_END);
    size_t size = (size_t)ftell(f);
    fseek(f, 0, SEEK_SET);
    out = (char *)malloc(1 + size * sizeof(char));
    fread(out, 1, size, f);
    out[size] = '\0';
    fclose(f);
    return out;
}

static uint32_t rsa_encrypt(uint32_t c, uint32_t n, uint32_t e)
{
    return mod_pow(c, e, n);
}

static uint32_t rsa_decrypt(uint32_t m, uint32_t n, uint32_t d)
{
    return mod_pow(m, d, n);
}

static void rsa_gmp_encrypt(const mpz_t c, const mpz_t n, const mpz_t e, mpz_t *out)
{
    mpz_powm(*out, c, e, n);
}

static void rsa_gmp_decrypt(const mpz_t m, const mpz_t n, const mpz_t d, mpz_t *out)
{
    mpz_powm(*out, m, d, n);
}

/**
 * @brief Computes a^b
 * @param a
 * @param b
 * @return a^b
 */
static uint32_t rsa_pow(uint32_t a, uint32_t b)
{
    uint32_t out = 1;
    while (b)
    {
        out *= a;
        b--;
    }
    return out;
}

/**
 * @brief Computes a mod b
 * @param a
 * @param b
 * @return a % b
 */
static uint32_t rsa_mod(uint32_t a, uint32_t b)
{
    return (a - b * (a / b));
}

/**
 * @brief Computes b^e mod m
 * @param b Base
 * @param e Exponent
 * @param m Modulus
 * @return b^e mod m
 */
static uint32_t mod_pow(uint32_t b, uint32_t e, uint32_t m)
{
    if (m == 0)
    {
        return 0;
    }
    uint32_t c = 1;
    for (uint32_t i = 0; i < e; i++)
    {
        c = rsa_mod((c * b), m);
    }
    return c;
}