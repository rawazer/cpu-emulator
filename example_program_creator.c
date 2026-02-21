#include <stdio.h>
#include <stdint.h>

/**
 * Simple program that calculates 5 + 4 + 3 + 2 + 1
 * Pseudocode:
 * R0 = 5
 * R1 = 0
 * Loop:
 * R1 += R0
 * R0 -= 1
 * If R0 != 0:
 * JMP Loop
 * Else:
 * HALT
 */
uint8_t program[] = {
    // Data section
    0x05,
    0x00,
    0x01,
    // Code section
    0x04, 0x00, // LD R0, RAM[0] (load data from RAM[0] to R0)
    0x04, 0x11, // LD R1, RAM[1] (load data from RAM[1] to R1)
    0x04, 0x22, // LD R2, RAM[2] (load data from RAM[2] to R2)
    0x04, 0x31, // LD R3, RAM[1] (load data from RAM[1] to R3)
    0x02, 0x10, // ADD R1, R0 (add R0 to R1)
    0x03, 0x02, // SUB R0, R2 (subtract R2 from R0)
    0x08, 0x03, // CMP R0, R3 (compare R0 and R3)
    0x07, 0x15, // JZ 0x15 (jump to 0x15 if ZF is 1)
    0x06, 0x0B, // JMP 0x0B (jump to 0x0B)
    0xFF // HALT
};

int main(int argc, char *argv[]) {
    FILE *file = fopen("program.bin", "wb");
    fwrite(program, 1, sizeof(program), file);
    fclose(file);

    return 0;
}
