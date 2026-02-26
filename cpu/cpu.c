#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../defines.h"
#include "cpu.h"

#define EXTRACT_REGS(operand, reg1, reg2) \
    reg1 = (operand >> 4) & 0x0F; \
    reg2 = operand & 0x0F;

void print_cpu(cpu_t *cpu) {
    printf("PC: %d\n", cpu->PC);
    printf("ZF: %d\n", cpu->ZF);
    printf("Program size: %d\n", cpu->rom_size_bytes);
    printf("ROM:\n");
    for (int i = 0; i < cpu->rom_size_bytes; i++) {
        printf("%02X ", cpu->ROM[i]);
    }
    printf("\n");
    printf("Registers:\n");
    for (int i = 0; i < NUM_REGS; i++) {
        printf("R%d: %02X\n", i, cpu->registers[i]);
    }
    printf("\n");
}

bool execute_instruction(cpu_t *cpu) {
    if (cpu->PC >= cpu->rom_size_bytes) {
        return false;
    }
    
    uint8_t reg1, reg2, addr;
    instruction_t instruction = {
        .opcode = cpu->ROM[cpu->PC++],
        .operand = 0,
    };
    
    if (instruction.opcode != OPCODE_HALT) {
        assert(cpu->PC < cpu->rom_size_bytes);
        instruction.operand = cpu->ROM[cpu->PC++];
    }

    switch (instruction.opcode) {
        case OPCODE_MOV:
            EXTRACT_REGS(instruction.operand, reg1, reg2);
            assert(reg1 < NUM_REGS);
            assert(reg2 < NUM_REGS);
            cpu->registers[reg1] = cpu->registers[reg2];
            return true;
        case OPCODE_ADD:
            EXTRACT_REGS(instruction.operand, reg1, reg2);
            assert(reg1 < NUM_REGS);
            assert(reg2 < NUM_REGS);
            cpu->registers[reg1] = cpu->registers[reg1] + cpu->registers[reg2];
            cpu->ZF = (cpu->registers[reg1] == 0);
            return true;
        case OPCODE_SUB:
            EXTRACT_REGS(instruction.operand, reg1, reg2);
            assert(reg1 < NUM_REGS);
            assert(reg2 < NUM_REGS);
            cpu->registers[reg1] = cpu->registers[reg1] - cpu->registers[reg2];
            cpu->ZF = (cpu->registers[reg1] == 0);
            return true;
        case OPCODE_LD:
            EXTRACT_REGS(instruction.operand, reg1, addr);
            assert(reg1 < NUM_REGS);
            assert(addr < cpu->ram_size_bytes);
            cpu->registers[reg1] = cpu->RAM[addr];
            return true;
        case OPCODE_ST:
            EXTRACT_REGS(instruction.operand, reg1, addr);
            assert(reg1 < NUM_REGS);
            assert(addr < cpu->ram_size_bytes);
            cpu->RAM[addr] = cpu->registers[reg1];
            return true;
        case OPCODE_JMP:
            assert(instruction.operand < cpu->rom_size_bytes);
            cpu->PC = instruction.operand;
            return true;
        case OPCODE_JZ:
            assert(instruction.operand < cpu->rom_size_bytes);
            if (cpu->ZF) {
                cpu->PC = instruction.operand;
            }
            return true;
        case OPCODE_CMP:
            EXTRACT_REGS(instruction.operand, reg1, reg2);
            assert(reg1 < NUM_REGS);
            assert(reg2 < NUM_REGS);
            cpu->ZF = cpu->registers[reg1] == cpu->registers[reg2];
            return true;
        case OPCODE_HALT:
            return false;
        default:
            assert(false);
    }
}
