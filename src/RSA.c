#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "../include/RSA.h"

static uint32_t rsa_pow(uint32_t m, uint32_t e);
static inline uint32_t rsa_mod(uint32_t a, uint32_t b);

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
            int c = rsa_mod(rsa_pow((uint32_t)in[i], e), n);
            fprintf(f, "%04" PRIX32 "(%c) ", c, (char)c);
        }
    }
    fseek(f, 0, SEEK_END);
    size_t size = (size_t)ftell(f);
    fseek(f, 0, SEEK_SET);
    out = (char *)malloc(1 + size * sizeof(char));
    fread(out, 1, size, f);
    for (int i = 0; i <= size; i++)
    {
        out[i] = (out[i] != '\0') * out[i] + (out[i] == '\0') * '0';
    }
    out[size] = '\0';
    fclose(f);
    return out;
}

static uint32_t rsa_pow(uint32_t m, uint32_t e)
{
    uint32_t out = 1;
    while (e)
    {
        out *= m;
        e--;
    }
    return out;
}

static inline uint32_t rsa_mod(uint32_t a, uint32_t b)
{
    return (a - b * (a / b));
}