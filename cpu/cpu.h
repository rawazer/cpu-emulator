#ifndef CPU_H
#define CPU_H

#include <stdbool.h>
#include "../defines.h"

void init_cpu(cpu_t *cpu);
void print_cpu(cpu_t *cpu);
bool execute_instruction(cpu_t *cpu);

#endif // CPU_H
