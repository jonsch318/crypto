/** @file module.h
 * 
 * @brief The module generates RSA key pairs from two prime numbers
 *
 */
#ifndef RSA_H_INCLUDED
#define RSA_H_INCLUDED
#include <stdint.h>
#include <gmp.h>

/**
 * @brief Generates RSA key pairs from two prime numbers
 * @param p the first prime number
 * @param q the secound prime number
 * @param ret_N the pointer to the uint32_t of the n value of the public and private key
 * @param ret_e the pointer to the uint32_t of the e value of the public key
 * @param ret_d the pointer to the uint32_t of the d value of the private key
 * @return (void)
 */
void RSA_get(uint32_t p, uint32_t q, uint32_t *ret_N, uint32_t *ret_e, uint32_t *ret_d);

/**
 * @brief Generates RSA key pairs from two prime numbers
 * @param p the first prime number
 * @param q the secound prime number
 * @param ret_N the pointer to the mpz_t of the n value of the public and private key
 * @param ret_e the pointer to the mpz_t of the e value of the public key
 * @param ret_d the pointer to the mpz_t of the d value of the private key
 * @return (void)
 */
void gmp_RSA_get(const mpz_t p, const mpz_t q, mpz_t *ret_N, mpz_t *ret_e, mpz_t *ret_d);

/**
 * @brief Encrypts a string with the specified key
 * @param in The input
 * @param n The N value of the public key
 * @param e The e value of the public key
 * @param out The output
 * @return 
 */
char *RSA_encrypt_string(const char *in, uint32_t n, uint32_t e, char *out);

#endif // RSA_H_INCLUDED