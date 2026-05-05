#include "parser.h"

struct Instruction parseInstruction(uint32_t instr) {
    struct Instruction parsedInstruction;
    parsedInstruction.instruction = instr;
    parsedInstruction.opcode = (instr << 25) >> 25;
    parsedInstruction.bits7_11 = (instr << 20) >> 27;
    parsedInstruction.bits12_14 = (instr << 17) >> 29;
    parsedInstruction.bits15_19 = (instr << 12) >> 27;
    parsedInstruction.bits20_24 = (instr << 7) >> 27;
    parsedInstruction.bits25_31 = instr >> 25;

    return parsedInstruction;
}