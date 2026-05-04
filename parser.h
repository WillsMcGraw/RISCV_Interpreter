#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>
#include "instruction.h"

struct Instruction parseInstruction(uint32_t instr);

#endif