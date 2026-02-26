#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include "program_loader/program_loader.h"
#include "cpu/cpu.h"

#define OK 0
#define ERROR 1

int main(int argc, char *argv[]) {
    int ret = ERROR;
    prg_load_status_t load_status = PRG_LOAD_FILE_NOT_FOUND;
    cpu_t cpu = { 0 };

    do {
        /* Load program */
        if (argc != 2) {
            printf("Please provide program to load as second argument.");
            break;
        }
        load_status = load_program(&cpu, argv[1]);
        if (PRG_LOAD_OK != load_status) {
            printf("Failed to load program: %d\n", load_status);
            break;
        }
        /* Execute program */
        do {
            print_cpu(&cpu);
        } while (execute_instruction(&cpu));

        ret = OK;
    } while (0);
    
    return ret;
}
