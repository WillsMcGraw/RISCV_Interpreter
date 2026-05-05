#ifndef TESTS_H
#define TESTS_H

#include <stdio.h>
#include <stdint.h>
#include "instruction.h"
#include "interpreter.h"
#include "parser.h"

extern uint32_t registers[];
extern uint32_t pc;
extern FILE *instructionLog;

void testManager();
int testRInstructions();
int testIInstructions();
void setRegistersToZero();

#endif