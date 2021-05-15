#ifndef HELPER_FUNCTIONS_H_INCLUDED
#define HELPER_FUNCTIONS_H_INCLUDED
#include <stdint.h>
#include <gmp.h>

/** \brief Tests whether a number is a prime number
 *
 * \param p is the number to be tested
 * \return 1 if the number is a prime number, otherwise 0
 *
 */
int is_prime(uint32_t p);

/**
 * @brief Generates a random prime number
 * @param n Range 0 to n
 * @return The prime number
 */
uint32_t prime_get(uint32_t n);

/**
 * @brief Generates a random prime number
 * @param n Range 0 to n
 * @param out The pointer to the output
 * @return (void)
 */
void prime_gmp_get(mp_bitcnt_t n, mpz_t *out);

void helper_functions_exit();

#endif // HELPER_FUNCTIONS_H_INCLUDED
