#ifndef XOR_H
#define XOR_H
/**
 * plaintext XOR key = ciphertext  <--->  ciphertext XOR key = plaintext
 */
#define xor_decrypt(inp, pass, outp) xor_encrypt(inp, pass, outp)

/**
 * @brief Encrypts a string with the given key
 * 
 * @param inp The plaintext
 * @param pass The key
 * @param outp The buffer for the ciphertext
 * @return int the size of the ciphertext
 */
int xor_encrypt(char *inp, char *pass, char *outp);

#endif // XOR_H
