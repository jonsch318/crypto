#include "../../../include/ui/ciphers/ui_xor.h"
#include "../../extern/c-terminal/include/terminal.h"
#include "../../../include/ciphers/xor.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief The " UI " for the XOR demo
 * @return (void)
 */
void m_xor(void)
{
    char inp[251];
    char out[251];
    char pass[251];
    int len = 0;
    terminal_clear();
    terminal_set_color(WHITE, BLACK);
    printf("XOR:\n");
    printf("Please enter the text to be encrypted (max. 250):\n");
    scanf("%250[^\n]s", inp);
    while (getchar() != '\n')
    {
    }
    printf("Please enter the key (max. 250):\n");
    scanf("%250[^\n]s", pass);
    len = xor_encrypt(inp, pass, out);
    terminal_clear();
    terminal_set_color(LIGHT_WHITE, BLACK);
    printf("Input:\n");
    terminal_set_color(WHITE, BLACK);
    printf("%s\n", inp);
    terminal_set_color(LIGHT_WHITE, BLACK);
    printf("ciphertext:\n");
    terminal_set_color(WHITE, BLACK);
    for (int i = 0; i <= len; i++)
    {
        switch (out[i])
        {
        case 0:
            printf("[NUL]");
            break;
        case 1:
            printf("[SOH]");
            break;
        case 2:
            printf("[STX]");
            break;
        case 3:
            printf("[ETX]");
            break;
        case 4:
            printf("[EOT]");
            break;
        case 5:
            printf("[ENQ]");
            break;
        case 6:
            printf("[ACK]");
            break;
        case 7:
            printf("[BEL]");
            break;
        case 8:
            printf("[BS]");
            break;
        case 9:
            printf("[TAB (HT)]");
            break;
        case 10:
            printf("[LF]");
            break;
        case 11:
            printf("[VT]");
            break;
        case 12:
            printf("[FF]");
            break;
        case 13:
            printf("[CR]");
            break;
        case 14:
            printf("[SO]");
            break;
        case 15:
            printf("[SI]");
            break;
        case 16:
            printf("[DLE]");
            break;
        case 17:
            printf("[DC1]");
            break;
        case 18:
            printf("[DC2]");
            break;
        case 19:
            printf("[DC3]");
            break;
        case 20:
            printf("[DC4]");
            break;
        case 21:
            printf("[NAK]");
            break;
        case 22:
            printf("[SYN]");
            break;
        case 23:
            printf("[ETB]");
            break;
        case 24:
            printf("[CAN]");
            break;
        case 25:
            printf("[EM]");
            break;
        case 26:
            printf("[SUB]");
            break;
        case 27:
            printf("[ESC]");
            break;
        case 28:
            printf("[FS]");
            break;
        case 29:
            printf("[GS]");
            break;
        case 30:
            printf("[RS]");
            break;
        case 31:
            printf("[US]");
            break;
        default:
            printf("%c", out[i]);
            break;
        }
    }
    printf("\n\n");
    terminal_set_color(LIGHT_WHITE, BLACK);
    printf("ciphertext[bytes]:\n");
    terminal_set_color(WHITE, BLACK);
    for (int i = 0; i <= len; i++)
    {
        printf("%u ", out[i]);
    }
    terminal_reset_color();
    getchar();
    printf("\nPress enter to return...");
    while (getchar() != '\n')
    {
    }
}