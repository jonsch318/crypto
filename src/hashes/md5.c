#include "../../include/hashes/md5.h"
#include <stdlib.h>
#include <stdio.h>
#ifdef USE_GMP
#include <gmp.h>

/**
 * @brief Creates the 128-bit md5 hash of a file
 *
 * @param path The path to the file
 * @param ret The hash
 * @return (void)
 */
void md5_hash_file(const char *path, mpz_t *ret)
{
}

/**
 * @brief Creates the 128-bit md5 hash of a string
 *
 * @param path The string
 * @param ret The hash
 * @return (void)
 */
void md5_hash_string(const char *str, mpz_t *ret)
{
}

/**
 * @brief Converts the hash to a string
 *
 * @param hash The hash
 * @param format Octal/decimal/hexadecimal
 * @return A pointer to the allocated string
 */
char *md5_hash_to_string(const mpz_t hash, MD5_FORMAT format)
{
    char *ret = NULL;
    switch (format)
    {
    case MD5_OCT:
        ret = (char *)calloc(44, sizeof(char));
        gmp_snprintf(ret, 44, "Zo");
        break;
    case MD5_DEC:
        ret = (char *)calloc(40, sizeof(char));
        gmp_snprintf(ret, 40, "Zd");
        break;
    case MD5_HEX:
        ret = (char *)calloc(34, sizeof(char));
        gmp_snprintf(ret, 34, "Za");
        break;
    }
    return ret;
}

#else
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>

#pragma GCC warning "md5 hashing may not be supported and lead to program termination"

/**
 * @brief Creates the 128-bit md5 hash of a file, if 128-bit integer are supported
 *
 * @param path The path to the file
 * @param ret The hash
 * @return (void)
 */
void md5_hash_file(const char *path, uintmax_t *ret)
{
    assert((sizeof(uintmax_t) < 16) && !!("128-bit integers are unsupported\n"));
    *ret = 0;
    return;
}

/**
 * @brief Creates the 128-bit md5 hash of a string, if 128-bit integer are supported
 *
 * @param path The string
 * @param ret The hash
 * @return (void)
 */
void md5_hash_string(const char *str, uintmax_t *ret)
{
    assert((sizeof(uintmax_t) < 16) && !!("128-bit integers are unsupported\n"));
    *ret = 0;
    return;
}

/**
 * @brief Converts the hash to a string
 *
 * @param hash The hash
 * @param format Octal/decimal/hexadecimal
 * @return A pointer to the allocated string or NULL if 128-bit integers are unsupported
 */
char *md5_hash_to_string(uintmax_t hash, MD5_FORMAT format)
{
    assert((sizeof(uintmax_t) < 16) && !!("128-bit integers are unsupported\n"));
    char *ret = NULL;
    switch (format)
    {
    case MD5_OCT:
        ret = (char *)calloc(44, sizeof(char));
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wshift-count-overflow"
        sprintf(ret, "%" PRIo64 "%" PRIo64 "", (hash >> 64), (hash & 0xFFFFFFFFFFFFFFFF));
        #pragma GCC diagnostic pop
        break;
    case MD5_DEC:
        ret = (char *)calloc(40, sizeof(char));
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wshift-count-overflow"
        sprintf(ret, "%" PRIu64 "%" PRIu64 "", (hash >> 64), (hash & 0xFFFFFFFFFFFFFFFF));
        #pragma GCC diagnostic pop
        break;
    case MD5_HEX:
        ret = (char *)calloc(34, sizeof(char));
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wshift-count-overflow"
        sprintf(ret, "%" PRIx64 "%" PRIx64 "", (hash >> 64), (hash & 0xFFFFFFFFFFFFFFFF));
        #pragma GCC diagnostic pop
        break;
    }
    return ret;
}

#endif