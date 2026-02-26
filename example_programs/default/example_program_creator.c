#include <stdio.h>
#include <stdint.h>

#define PC_ENTRY_POINT 0

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
uint8_t ROM[] = {
    0x04, 0x00, // LD R0, RAM[0] (load data from RAM[0] to R0)
    0x04, 0x11, // LD R1, RAM[1] (load data from RAM[1] to R1)
    0x04, 0x22, // LD R2, RAM[2] (load data from RAM[2] to R2)
    0x04, 0x31, // LD R3, RAM[1] (load data from RAM[1] to R3)
    0x02, 0x10, // ADD R1, R0 (add R0 to R1)
    0x03, 0x02, // SUB R0, R2 (subtract R2 from R0)
    0x08, 0x03, // CMP R0, R3 (compare R0 and R3)
    0x07, 0x12, // JZ 0x12 (jump to 0x12 if ZF is 1)
    0x06, 0x08, // JMP 0x08 (jump to 0x08)
    0xFF // HALT
};
uint8_t RAM[] = {
    0x05,
    0x00,
    0x01,
};

int main(int argc, char *argv[]) {
    uint8_t pc_entry_point = PC_ENTRY_POINT;
    uint8_t size_of_rom = sizeof(ROM);
    uint8_t size_of_ram = sizeof(RAM);
    FILE *file = fopen("./out/prg.bin", "wb");
    fwrite(&pc_entry_point, 1, 1, file);
    fwrite(&size_of_rom, 1, 1, file);
    fwrite(&size_of_ram, 1, 1, file);
    fwrite(ROM, 1, size_of_rom, file);
    fwrite(RAM, 1, size_of_ram, file);
    fclose(file);

    return 0;
}
