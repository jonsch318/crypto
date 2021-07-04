#include "../../include/ciphers/xor.h"
#include <stdlib.h>

int xor_encrypt(char *inp, char *pass, char *outp)
{
    char *inp_p = inp;
    char *pass_p = pass;
    int inp_len = 0;
    int pass_len = 0;
    //Return if the input is invalid
    if (inp == NULL || pass == NULL)
    {
        return -1;
    }
    //Get the input size
    while (*(inp_p++) != '\0')
    {
        inp_len++;
    }
    //Get the key size
    while (*(pass_p++) != '\0')
    {
        pass_len++;
    }
    //Allocate memory for output if outp == NULL
    if (outp == NULL)
    {
        outp = (char *)malloc(inp_len * sizeof(char) + 1);
        outp[inp_len] = '\0';
    }
    //Xor cipher
    for (int i = 0; inp[i] != '\0'; i++)
    {
        outp[i] = inp[i] ^ pass[i % pass_len];
    }
    return inp_len;
}