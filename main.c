#include <stdio.h>
#include <stdint.h>

#include "instruction.h"
#include "parser.h"
#include "interpreter.h"
#include "tests.h"

#define MEM_SIZE (1024 * 1024) // 1 MB

void printRegisters(uint32_t registers[]);

FILE *instructionLog;

uint32_t registers[32];
uint32_t pc;
uint8_t memory[MEM_SIZE];

int main(int argc, char *argv[]) {
    instructionLog = fopen("instructionLog.txt", "w");

    testManager();

    fclose(instructionLog);
    return 0;
}

void printRegisters(uint32_t registers[]) {
    for (uint32_t i = 0; i < 32; i++) {
        printf("Register %d: %d\n", i, registers[i]);
    }
}