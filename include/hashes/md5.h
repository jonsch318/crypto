#ifndef MD5_H
#define MD5_H

typedef enum
{
    MD5_OCT=8,
    MD5_DEC=10,
    MD5_HEX=16
} MD5_FORMAT;

#ifdef USE_GMP
#include <gmp.h>

/**
 * @brief Creates the 128-bit md5 hash of a file
 *
 * @param path The path to the file
 * @param ret The hash
 * @return (void)
 */
void md5_hash_file(const char *path, mpz_t *ret);

/**
 * @brief Creates the 128-bit md5 hash of a string
 *
 * @param path The string
 * @param ret The hash
 * @return (void)
 */
void md5_hash_string(const char *str, mpz_t *ret);

/**
 * @brief Converts the hash to a string
 *
 * @param hash The hash
 * @param format Octal/decimal/hexadecimal
 * @return A pointer to the allocated string
 */
char *md5_hash_to_string(const mpz_t hash, MD5_FORMAT format);

#else

#include <stdint.h>

/**
 * @brief Creates the 128-bit md5 hash of a file, if 128 integer are supported
 *
 * @param path The path to the file
 * @param ret The hash
 * @return (void)
 */
void md5_hash_file(const char *path, uintmax_t *ret);

/**
 * @brief Creates the 128-bit md5 hash of a string, if 128 integer are supported
 *
 * @param path The string
 * @param ret The hash
 * @return (void)
 */
void md5_hash_string(const char *str, uintmax_t *ret);

/**
 * @brief Converts the hash to a string
 *
 * @param hash The hash
 * @param format Octal/decimal/hexadecimal
 * @return A pointer to the allocated string or NULL if 128-bit integers are unsupported
 */
char *md5_hash_to_string(uintmax_t hash, MD5_FORMAT format);
#endif

#endif // MD5_H
