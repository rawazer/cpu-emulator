#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../defines.h"
#include "cpu.h"

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

static uint8_t fetch_byte(cpu_t *cpu) {
    assert(cpu->PC < cpu->rom_size_bytes);
    return cpu->ROM[cpu->PC++];
}

static void extract_regs(cpu_t *cpu, uint8_t *reg1, uint8_t *reg2) {
    uint8_t operand = fetch_byte(cpu);
    *reg1 = (operand >> 4) & 0x0F;
    *reg2 = operand & 0x0F;
}

bool execute_instruction(cpu_t *cpu) {
    uint8_t opcode = 0, reg1 = 0, reg2 = 0, addr = 0, imm8 = 0;

    if (cpu->PC >= cpu->rom_size_bytes) {
        return false;
    }

    opcode = fetch_byte(cpu);
    switch (opcode) {
        case OPCODE_MOV:
            extract_regs(cpu, &reg1, &reg2);
            assert(reg1 < NUM_REGS);
            assert(reg2 < NUM_REGS);
            cpu->registers[reg1] = cpu->registers[reg2];
            return true;
        case OPCODE_ADD:
            extract_regs(cpu, &reg1, &reg2);
            assert(reg1 < NUM_REGS);
            assert(reg2 < NUM_REGS);
            cpu->registers[reg1] = cpu->registers[reg1] + cpu->registers[reg2];
            cpu->ZF = (cpu->registers[reg1] == 0);
            return true;
        case OPCODE_SUB:
            extract_regs(cpu, &reg1, &reg2);
            assert(reg1 < NUM_REGS);
            assert(reg2 < NUM_REGS);
            cpu->registers[reg1] = cpu->registers[reg1] - cpu->registers[reg2];
            cpu->ZF = (cpu->registers[reg1] == 0);
            return true;
        case OPCODE_LD:
            reg1 = fetch_byte(cpu);
            addr = fetch_byte(cpu);
            assert(reg1 < NUM_REGS);
            assert(addr < cpu->ram_size_bytes);
            cpu->registers[reg1] = cpu->RAM[addr];
            return true;
        case OPCODE_ST:
            reg1 = fetch_byte(cpu);
            addr = fetch_byte(cpu);
            assert(reg1 < NUM_REGS);
            assert(addr < cpu->ram_size_bytes);
            cpu->RAM[addr] = cpu->registers[reg1];
            return true;
        case OPCODE_JMP:
            addr = fetch_byte(cpu);
            assert(addr < cpu->rom_size_bytes);
            cpu->PC = addr;
            return true;
        case OPCODE_JZ:
        addr = fetch_byte(cpu);
            assert(addr < cpu->rom_size_bytes);
            if (cpu->ZF) {
                cpu->PC = addr;
            }
            return true;
        case OPCODE_CMP:
            extract_regs(cpu, &reg1, &reg2);
            assert(reg1 < NUM_REGS);
            assert(reg2 < NUM_REGS);
            cpu->ZF = cpu->registers[reg1] == cpu->registers[reg2];
            return true;
        case OPCODE_LDI:
            reg1 = fetch_byte(cpu);
            imm8 = fetch_byte(cpu);
            assert(reg1 < NUM_REGS);
            cpu->registers[reg1] = imm8;
            return true;
        case OPCODE_HALT:
            return false;
        default:
            assert(false);
    }
}
