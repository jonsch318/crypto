/** @file module.h
 * 
 * @brief The module generates RSA key pairs from two prime numbers
 *
 */ 
#ifndef RSA_H_INCLUDED
#define RSA_H_INCLUDED
#include <stdint.h>

/**
 * @brief Generates RSA key pairs from two prime numbers
 * @param p the first prime number
 * @param q the secound prime number
 * @param ret_N the pointer to the uint32_t of the n value of the public and private key
 * @param ret_e the pointer to the uint32_t of the e value of the public key
 * @param ret_d the pointer to the uint32_t of the d value of the private key
 * @return (void)
 */
void RSA_get(uint32_t p,uint32_t q, uint32_t *ret_N, uint32_t *ret_e, uint32_t *ret_d);

#endif // RSA_H_INCLUDED