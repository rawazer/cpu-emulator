import os
import sys
import subprocess

DEFAULT_PROGRAM_CREATOR = "example_programs/default/example_program_creator.c"

def main():
    os.makedirs("out", exist_ok=True)
    prg_crt_cmpl_res = subprocess.run(["gcc", "-Wall", "-Wextra", "-Werror", DEFAULT_PROGRAM_CREATOR, "-o", "out/prg_creator.bin"])
    if (prg_crt_cmpl_res.returncode != 0):
        sys.exit(f"prg_crt_cmpl_res: {prg_crt_cmpl_res.returncode}")
    prg_crt_res = subprocess.run(["./out/prg_creator.bin"])
    if (prg_crt_res.returncode != 0):
        sys.exit(f"prg_crt_res: {prg_crt_res.returncode}")
    cpu_cmpl_res = subprocess.run(["gcc", "-Wall", "-Wextra", "-Werror", "main.c", "cpu/cpu.c", "program_loader/program_loader.c", "-o", "out/cpu.bin"])
    if (cpu_cmpl_res.returncode != 0):
        sys.exit(f"cpu_cmpl_res: {cpu_cmpl_res.returncode}")

if __name__ == "__main__":
    main()
