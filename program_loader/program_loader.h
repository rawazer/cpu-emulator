#ifndef PROGRAM_LOADER_H
#define PROGRAM_LOADER_H

#include "../defines.h"

typedef enum {
    PRG_LOAD_OK = 0,
    PRG_LOAD_FILE_NOT_FOUND = 1,
    PRG_LOAD_FILE_INVALID_SIZE = 2,
    PRG_LOAD_FILE_INVALID_FORMAT = 3,
} prg_load_status_t;

prg_load_status_t load_program(cpu_t *cpu, const char *filename);

#endif // PROGRAM_LOADER_H
