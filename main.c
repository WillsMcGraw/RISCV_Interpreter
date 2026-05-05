#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "instruction.h"
#include "parser.h"
#include "interpreter.h"
#include "basic_instruction_testing.h"

#define MEM_SIZE (1024 * 1024) // 1 MB

void printRegisters();
void initialize();

FILE *instructionLog;

uint32_t registers[32];
uint32_t pc;
uint8_t memory[MEM_SIZE];

int main(int argc, char *argv[]) {
    // Check arguments
    if (argc != 2) {
        perror("Incorrect number of arguments passed: main.exe [program_to_interpret]\n");
        return 1;
    }

    // Prep environment
    memset(memory, 0, MEM_SIZE);
    memset(registers, 0, 32 * 4);
    instructionLog = fopen("instructionLog.txt", "w");
    FILE *program = fopen(argv[1], "rb");
    size_t programLength = fread(memory, 1, MEM_SIZE, program);
    // Set the stack pointer & return address
    registers[2] = MEM_SIZE - 4;
    registers[1] = 0x0000FFFF;
    
    // Run program, note: pc is updated in interpret()
    int program_status = 1;
    while (program_status && pc + 3 < programLength) {
        uint32_t instruction = loadWord(pc);
        struct Instruction parsed_instruction = parseInstruction(instruction);
        program_status = interpret(parsed_instruction);

        printf("PC: %u, Instruction: %08x\n", pc, instruction);
        printf("Instruction handled\n");
    }

    printRegisters();

    //testManager();

    fclose(instructionLog);
    fclose(program);
    return 0;
}

void printRegisters() {
    for (int i = 0; i < 32; i++) {
        printf("Register %d: %d\n", i, registers[i]);
    }
}