| Opcode | Operands (bytes) | Operand 1 | Operand 2 | Instruction    | Description          |
| ------ | ---------------- | --------- | --------- | -------------- | -------------------- |
| 0x01   | 1                | [ Rd|Rs ] |           | MOV Rd, Rs     | Rd = Rs              |
| 0x02   | 1                | [ Rd|Rs ] |           | ADD Rd, Rs     | Rd += Rs             |
| 0x03   | 1                | [ Rd|Rs ] |           | SUB Rd, Rs     | Rd -= Rs             |
| 0x04   | 2                | [ Rd ]    | [ addr ]  | LOAD Rd, addr  | Rd = RAM[addr]       |
| 0x05   | 2                | [ Rs ]    | [ addr ]  | STORE Rs, addr | RAM[addr] = Rs       |
| 0x06   | 1                | [ addr ]  |           | JMP addr       | PC = addr            |
| 0x07   | 1                | [ addr ]  |           | JZ addr        | if ZF==1 → PC = addr |
| 0x08   | 1                | [ Rd|Rs ] |           | CMP Rd, Rs     | ZF = (Rd == Rs)      |
| 0x09   | 2                | [ Rd ]    | [ imm8 ]  | LDI Rd, imm8   | Rd = imm8            |
| 0xFF   | 0                |           |           | HALT           | stop execution       |
