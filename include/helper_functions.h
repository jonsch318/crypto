#ifndef HELPER_FUNCTIONS_H_INCLUDED
#define HELPER_FUNCTIONS_H_INCLUDED
#include <stdint.h>

/** \brief Tests whether a number is a prime number
 *
 * \param p is the number to be tested
 * \return 1 if the number is a prime number, otherwise 0
 *
 */
int is_prime(uint32_t p);

/**
 * @brief Generates a random prime number
 * @return The prime number
 */
uint32_t get_prime();

#endif // HELPER_FUNCTIONS_H_INCLUDED
