#include <stdio.h>
#include <stdbool.h>
#include "../defines.h"
#include "program_loader.h"

static int file_size(FILE *file) {
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

static bool is_file_too_large(FILE *file) {
    return file_size(file) > RAM_SIZE_BYTES;
}

prg_load_status_t load_program(cpu_t *cpu, const char *filename) {
    prg_load_status_t ret = PRG_LOAD_FILE_NOT_FOUND;
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Failed to open file %s\n", filename);
        return PRG_LOAD_FILE_NOT_FOUND;
    }

    do {
        if (is_file_too_large(file)) {
            ret = PRG_LOAD_FILE_TOO_LARGE;
            break;
        }
        cpu->program_size_bytes = fread(cpu->RAM, 1, RAM_SIZE_BYTES, file);
        if (cpu->program_size_bytes == 0) {
            ret = PRG_LOAD_FILE_EMPTY;
            break;
        }
        ret = PRG_LOAD_OK;
    } while (0);

    fclose(file);
    return ret;
}
