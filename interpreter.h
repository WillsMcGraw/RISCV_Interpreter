#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdio.h>
#include <stdint.h>
#include "instruction.h"

extern uint32_t registers[];
extern uint32_t pc;
extern uint8_t memory[];
extern FILE *instructionLog;

int interpret(struct Instruction instr);
int handleRInstruction(struct Instruction instr);
int handleIInstruction(struct Instruction instr);
int handleILoadInstruction(struct Instruction instr);
int handleSInstruction(struct Instruction instr);
int handleBInstruction(struct Instruction instr);
int handleULuiInstruction(struct Instruction instr);
int handleUAuipcInstruction(struct Instruction instr);
int handleJJalInstruction(struct Instruction instr);
int handleIJalrInstruction(struct Instruction instr);
int handleIEcallEbreakInstruction(struct Instruction instr);

uint32_t loadWord(uint32_t offset);
uint32_t loadHalf(uint32_t offset);
uint32_t loadByte(uint32_t offset);
void saveWord(uint32_t offset, uint32_t word);
void saveHalf(uint32_t offset, uint32_t word);
void saveByte(uint32_t offset, uint32_t word);

#endif