#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdio.h>
#include <stdint.h>
#include "instruction.h"

extern uint32_t registers[];
extern uint32_t pc;
extern uint8_t memory[];
extern FILE *instructionLog;

void interpret(struct Instruction instr);
void handleRInstruction(struct Instruction instr);
void handleIInstruction(struct Instruction instr);
void handleILoadInstruction(struct Instruction instr);
void handleSInstruction(struct Instruction instr);
void handleBInstruction(struct Instruction instr);
void handleULuiInstruction(struct Instruction instr);
void handleUAuipcInstruction(struct Instruction instr);
void handleJJalInstruction(struct Instruction instr);
void handleIJalrInstruction(struct Instruction instr);

uint32_t loadWord(uint32_t offset);
uint32_t loadHalf(uint32_t offset);
uint32_t loadByte(uint32_t offset);
void saveWord(uint32_t offset, uint32_t word);
void saveHalf(uint32_t offset, uint32_t word);
void saveByte(uint32_t offset, uint32_t word);

#endif