#ifndef DEFINES_H
#define DEFINES_H

#include <stdint.h>

#define RAM_SIZE_BYTES 256
#define NUM_REGS 4

typedef enum {
    OPCODE_MOV = 0x01,
    OPCODE_ADD = 0x02,
    OPCODE_SUB = 0x03,
    OPCODE_LD = 0x04,
    OPCODE_ST = 0x05,
    OPCODE_JMP = 0x06,
    OPCODE_JZ = 0x07,
    OPCODE_CMP = 0x08,
    OPCODE_HALT = 0xFF
} opcode_t;

typedef struct {
    uint8_t opcode;
    uint8_t operand;
} instruction_t;

typedef struct {
    uint8_t registers[NUM_REGS];
    uint8_t PC;
    uint8_t ZF;
    uint8_t RAM[RAM_SIZE_BYTES];
    uint8_t program_size_bytes;
} cpu_t;

#endif // DEFINES_H
