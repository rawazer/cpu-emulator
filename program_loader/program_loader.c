#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "../defines.h"
#include "program_loader.h"

typedef struct {
    uint8_t entry_point;
    uint8_t rom_size;
    uint8_t ram_size;
} prg_header_t;

static size_t get_program_file_size(FILE *file) {
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

static void parse_program_header(FILE *prg_file, prg_header_t *prg_header) {
    assert(sizeof(prg_header->entry_point) == fread(&prg_header->entry_point, sizeof(prg_header->entry_point), 1, prg_file));
    assert(sizeof(prg_header->rom_size) == fread(&prg_header->rom_size, sizeof(prg_header->rom_size), 1, prg_file));
    assert(sizeof(prg_header->ram_size) == fread(&prg_header->ram_size, sizeof(prg_header->ram_size), 1, prg_file));
    printf("%d %d %d\n", prg_header->entry_point, prg_header->rom_size, prg_header->ram_size);
}

static bool program_header_valid(prg_header_t *program_header, size_t prg_size) {

    bool valid = false;

    do {
        // Check header validity on its own
        if (program_header->rom_size > MAX_ROM_SIZE_BYTES || program_header->ram_size > MAX_RAM_SIZE_BYTES) {
            break;
        }
        if (program_header->entry_point >= program_header->rom_size) {
            break;
        }

        // Check file validity according to header
        if (PROGRAM_HEADER_SIZE_BYTES + program_header->rom_size + program_header->ram_size != prg_size) {
            break;
        }
        valid = true;
    } while (0);

    return valid;
}

prg_load_status_t load_program(cpu_t *cpu, const char *filename) {
    size_t prg_size = 0;
    FILE *prg_file = NULL;
    prg_header_t prg_header = { 0 };
    prg_load_status_t ret = PRG_LOAD_FILE_NOT_FOUND;

    do {
        /* Open program to file */
        prg_file = fopen(filename, "rb");
        if (!prg_file) {
            printf("Failed to open file %s\n", filename);
            ret = PRG_LOAD_FILE_NOT_FOUND;
            break;
        }

        /* Validate program size */
        prg_size = get_program_file_size(prg_file);
        if (prg_size < MIN_PROGRAM_FILE_SIZE_BYTES || prg_size > MAX_PROGRAM_FILE_SIZE_BYTES) {
            printf("Invalid program size %lu\n", prg_size);
            ret = PRG_LOAD_FILE_INVALID_SIZE;
            break;
        }

        /* Validate program header */
        parse_program_header(prg_file, &prg_header);
        if (!program_header_valid(&prg_header, prg_size)) {
            printf("Invalid program header\n");
            ret = PRG_LOAD_FILE_INVALID_FORMAT;
            break;
        }

        /* Load program to CPU */
        cpu->PC = prg_header.entry_point;
        cpu->rom_size_bytes = prg_header.rom_size;
        cpu->ram_size_bytes = prg_header.ram_size;
        assert(prg_header.rom_size == fread(cpu->ROM, sizeof(uint8_t), prg_header.rom_size, prg_file));
        assert(prg_header.ram_size == fread(cpu->RAM, sizeof(uint8_t), prg_header.ram_size, prg_file));
        ret = PRG_LOAD_OK;
    } while (0);

    fclose(prg_file);
    return ret;
}
