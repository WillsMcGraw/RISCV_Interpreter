#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdint.h>

struct Instruction {
    uint32_t instruction;
    uint8_t opcode;
    uint8_t bits7_11;
    uint8_t bits12_14;
    uint8_t bits15_19;
    uint8_t bits20_24;
    uint8_t bits25_31;
};

#endif // INSTRUCTION_H