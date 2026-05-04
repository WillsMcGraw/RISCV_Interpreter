#include "interpreter.h"

/**
 * This function pulls the opcode from the instruction, and calls the
 * appropriate method to execute the corresponding instruction type.
 */
int interpret(struct Instruction instr) {
    int out;

    switch(instr.opcode) {
        // R Type Instructions
        case 0b0110011:
            out = handleRInstruction(instr);
            break;
        // I Type Instructions
        case 0b0010011:
            out = handleIInstruction(instr);
            break;
        // I Type Load Instructions
        case 0b0000011:
            out = handleILoadInstruction(instr);
            break;
        // S Type Instructions
        case 0b0100011:
            out = handleSInstruction(instr);
            break;
        // B Type Instructions
        case 0b1100011:
            out = handleBInstruction(instr);
            break;
        // U Type lui Instructions
        case 0b0110111:
            out = handleULuiInstruction(instr);
            break;
        // U Type auipc Instructions
        case 0b0010111:
            out = handleUAuipcInstruction(instr);
            break;
        // J Type jal Instructions
        case 0b1101111:
            out = handleJJalInstruction(instr);
            break;
        // I Type jalr Instructions
        case 0b1100111:
            out = handleIJalrInstruction(instr);
            break;
        // I Type ecall & ebreak Instructions
        case 0b1110011:
            out = handleIEcallEbreakInstruction(instr);
            break;
        // Unknown Instructions
        default:
            fprintf(instructionLog, "Unrecognized Instruction Detected\n");
            out = 0;
    }

    // Register 0 must always hold the value of 0.
    registers[0] = 0;

    return out;
}

/**
 * This function handles any R-type instructions.
 */
int handleRInstruction(struct Instruction instr) {
    uint8_t rd = instr.bits7_11;
    uint8_t rs1 = instr.bits15_19;
    uint8_t rs2 = instr.bits20_24;
    uint8_t funct3 = instr.bits12_14;
    uint8_t funct7 = instr.bits25_31;

    switch (funct3) {
        // add & sub Instructions
        case 0x0:
            // add Instruction
            if (funct7 == 0x00) {
                registers[rd] = registers[rs1] + registers[rs2];
                fprintf(instructionLog, "R Type add Interpreted\n");
            }
            // sub Instruction
            else if (funct7 == 0x20) {
                registers[rd] = registers[rs1] - registers[rs2];
                fprintf(instructionLog, "R Type sub Interpreted\n");
            }
            // Unknown Instruction
            else {
                fprintf(instructionLog, "Unrecognized R Instruction Detected\n");
                perror("Unrecognized R Instruction Interpreted\n");
                return 0;
            }
            break;
        // xor Instruction
        case 0x4:
            registers[rd] = registers[rs1] ^ registers[rs2];
            fprintf(instructionLog, "R Type xor Interpreted\n");
            break;
        // or Instruction
        case 0x6:
            registers[rd] = registers[rs1] | registers[rs2];
            fprintf(instructionLog, "R Type or Interpreted\n");
            break;
        // and instruction
        case 0x7:
            registers[rd] = registers[rs1] & registers[rs2];
            fprintf(instructionLog, "R Type and Interpreted\n");
            break;
        // sll Instruction
        case 0x1:
            registers[rd] = registers[rs1] << (registers[rs2] & 0x1F);
            fprintf(instructionLog, "R Type sll Interpreted\n");
            break;
        // srl & sra Instruction
        case 0x5:
            // srl Instruction
            if (funct7 == 0x00) {
                registers[rd] = registers[rs1] >> (registers[rs2] & 0x1F);
                fprintf(instructionLog, "R Type srl Interpreted\n");
            }
            // sra Instruction
            else if (funct7 == 0x20) {
                registers[rd] = ((int32_t) registers[rs1]) >> (registers[rs2] & 0x1F);
                fprintf(instructionLog, "R Type sra Interpreted\n");
            }
            // Unknown Instruction
            else {
                fprintf(instructionLog, "Unrecognized R Instruction Detected\n");
                perror("Unrecognized R Instruction Interpreted\n");
                return 0;
            }
            break;
        // slt Instruction
        case 0x2:
            if (((int32_t)registers[rs1]) < ((int32_t)registers[rs2])) {
                registers[rd] = 1;
            }
            else {
                registers[rd] = 0;
            }
            break;
        // sltu Instruction
        case 0x3:
            if (registers[rs1] < registers[rs2]) {
                registers[rd] = 1;
            }
            else {
                registers[rd] = 0;
            }
            break;
        // Unknown Instruction
        default:
            fprintf(instructionLog, "Unrecognized R Instruction Interpreted\n");
            perror("Unrecognized R Instruction Interpreted\n");
            return 0;
    }

    pc += 4;
    return 1;
}

/**
 * This method handles any I type instructions.
 */
int handleIInstruction(struct Instruction instr) {
    uint8_t rd = instr.bits7_11;
    uint8_t rs1 = instr.bits15_19;
    int32_t imm = (instr.bits25_31 << 5) | (instr.bits20_24);
    imm = (imm << 20) >> 20;
    uint8_t imm5_11 = instr.bits25_31;
    uint8_t imm0_4 = instr.bits20_24;
    uint8_t funct3 = instr.bits12_14;

    switch (funct3) {
        // addi Instruction
        case 0x0: 
            registers[rd] = registers[rs1] + imm;
            fprintf(instructionLog, "I Type addi Instruction Interpreted\n");
            break;
        // xori Instruction
        case 0x4:
            registers[rd] = registers[rs1] ^ imm;
            fprintf(instructionLog, "I Type xori Instruction Interpreted\n");
            break;
        // ori Instruction
        case 0x6:
            registers[rd] = registers[rs1] | imm;
            fprintf(instructionLog, "I Type ori Instruction Interpreted\n");
            break;
        // andi Instruction
        case 0x7:
            registers[rd] = registers[rs1] & imm;
            fprintf(instructionLog, "I Type andi Instruction Interpreted\n");
            break;
        // slli Instruction 
        case 0x1:
            if (imm5_11 == 0x00) {
                registers[rd] = registers[rs1] << imm0_4;
                fprintf(instructionLog, "I Type slli Instruction Interpreted\n");
                break;
            }
            fprintf(instructionLog, "Unrecognized I Instruction Detected\n");
            perror("Unrecognized I Instruction Detected\n");
            return 0;
            break;
        // srli & srai Instruction
        case 0x5:
            if (imm5_11 == 0x00) {
                registers[rd] = registers[rs1] >> imm0_4;
                fprintf(instructionLog, "I Type srli Instruction Interpreted\n");
                break;
            }
            else if (imm5_11 == 0x20) {
                registers[rd] = ((int32_t)registers[rs1]) >> imm0_4;
                fprintf(instructionLog, "I Type srai Instruction Interpreted\n");
                break;
            }
            fprintf(instructionLog, "Uncreognized I Instruction Detected\n");
            perror("Unrecognized I Instruction Detected\n");
            return 0;
            break;
        // slti Instruction
        case 0x2:
            if (((int32_t)registers[rs1]) < (imm)) {
                registers[rd] = 1;
            }
            else {
                registers[rd] = 0;
            }
            fprintf(instructionLog, "I Type slti Instruction Interpreted\n");
            break;
        // sltiu Instruction
        case 0x3:
            if (registers[rs1] < imm) {
                registers[rd] = 1;
            }
            else {
                registers[rd] = 0;
            }
            fprintf(instructionLog, "I Type sltiu Instruction Interpreted\n");
            break;
        default: 
            fprintf(instructionLog, "Unrecognized I Instruction Detected\n");
            perror("Unrecognized I Instruction Detected\n");
            return 0;
    }

    pc += 4;
    return 1;
}

/**
 * This method handles any I type load instructions.
 */
int handleILoadInstruction(struct Instruction instr) {
    uint8_t rd = instr.bits7_11;
    uint8_t rs1 = instr.bits15_19;
    int32_t imm = (instr.bits25_31 << 5) | (instr.bits20_24);
    imm = (imm << 20) >> 20;
    uint8_t funct3 = instr.bits12_14;

    switch (funct3) {
        // lb Instruction
        case 0x0:
            registers[rd] = (int32_t)(int8_t)loadByte(registers[rs1] + imm);
            fprintf(instructionLog, "I Type lb Instruction Interpreted\n");
            break;
        // lh Instruction
        case 0x1:
            registers[rd] = (int32_t)(int16_t)loadHalf(registers[rs1] + imm);
            fprintf(instructionLog, "I Type lh Instruction Interpreted\n");
            break;
        // lw Instruction
        case 0x2:
            registers[rd] = loadWord(registers[rs1] + imm);
            fprintf(instructionLog, "I Type lw Instruction Interpreted\n");
            break;
        // lbu Instruction
        case 0x4:
            registers[rd] = loadByte(registers[rs1] + imm);
            fprintf(instructionLog, "I Type lbu Instruction Interpreted\n");
            break;
        // lhu Instruction
        case 0x5:
            registers[rd] = loadHalf(registers[rs1] + imm);
            fprintf(instructionLog, "I Type lhu Instruction Interpreted\n");
            break;
        default:
            fprintf(instructionLog, "Unrecognized I Instruction Detected\n");
            perror("Unrecognized I Instruction Detected\n");
            return 0;
    }

    pc += 4;
    return 1;
}

/**
 * This method handles any S type instructions.
 */
int handleSInstruction(struct Instruction instr) {
    uint8_t rs1 = instr.bits15_19;
    uint8_t rs2 = instr.bits20_24;  
    int32_t imm = (instr.bits25_31 << 5) | (instr.bits7_11);
    imm = (imm << 20) >> 20;
    uint8_t funct3 = instr.bits12_14;

    switch (funct3) {
        // sb Instruction
        case 0x0:
            saveByte(registers[rs1] + imm, registers[rs2]);
            fprintf(instructionLog, "S Type sb Instruction Interpreted\n");
            break;
        // sh Instruction
        case 0x1:
            saveHalf(registers[rs1] + imm, registers[rs2]);
            fprintf(instructionLog, "S Type sh Instruction Interpreted\n");
            break;
        // sw Instruction
        case 0x2:
            saveWord(registers[rs1] + imm, registers[rs2]);
            fprintf(instructionLog, "S Type sw Instruction Interpreted\n");
            break;
        default:
            fprintf(instructionLog, "Unrecognized S Instruction Detected\n");
            perror("Unrecognized S Instruction Detected\n");
            return 0;
    }

    pc += 4;
    return 1;
}

/**
 * This method handles any B type instructions.
 */
int handleBInstruction(struct Instruction instr) {
    uint8_t rs1 = instr.bits15_19;
    uint8_t rs2 = instr.bits20_24;  
    int32_t imm = ((instr.bits25_31 & 0x40) << 6) | ((instr.bits7_11 & 0x01) << 11) | ((instr.bits25_31 & 0x3F) << 5) | ((instr.bits7_11 & 0x1E));
    imm = (imm << 19) >> 19;
    uint8_t funct3 = instr.bits12_14;

    switch (funct3) {
        // beq Instruction
        case 0x0:
            if (registers[rs1] == registers[rs2]) {
                pc += imm;
            }
            else {
                pc += 4;
            }
            fprintf(instructionLog, "B Type beq Instruction Interpreted");
            break;
        // bne Instruction
        case 0x1:
            if (registers[rs1] != registers[rs2]) {
                pc += imm;
            }
            else {
                pc += 4;
            }
            fprintf(instructionLog, "B Type bne Instruction Interpreted");
            break;
        // blt Instruction
        case 0x4:
            if ((int32_t)registers[rs1] < (int32_t)registers[rs2]) {
                pc += imm;
            }
            else {
                pc += 4;
            }
            fprintf(instructionLog, "B Type blt Instruction Interpreted");
            break;
        // bge Instruction
        case 0x5:
            if ((int32_t)registers[rs1] >= (int32_t)registers[rs2]) {
                pc += imm;
            }
            else {
                pc += 4;
            }
            fprintf(instructionLog, "B Type bge Instruction Interpreted");
            break;
        // bltu Instruction
        case 0x6:
            if (registers[rs1] < registers[rs2]) {
                pc += imm;
            }
            else {
                pc += 4;
            }
            fprintf(instructionLog, "B Type bltu Instruction Interpreted");
            break;
        // bgeu Instruction
        case 0x7:
            if (registers[rs1] >= registers[rs2]) {
                pc += imm;
            }
            else {
                pc += 4;
            }
            fprintf(instructionLog, "B Type bgeu Instruction Interpreted");
            break;
        default:
            fprintf(instructionLog, "Unrecognized B Type Instruction Detected");
            perror("Unrecognized B Instruction Detected\n");
            return 0;
    }

    return 1;
}

/**
 * This method handles U type instructions, specifically the lui instruction.
 */
int handleULuiInstruction(struct Instruction instr) {
    uint8_t rd = instr.bits7_11;
    int32_t imm = ((instr.bits25_31 << 25) 
        | (instr.bits20_24 << 20) 
        | (instr.bits15_19 << 15) 
        | (instr.bits12_14 << 12));

    registers[rd] = imm;
    fprintf(instructionLog, "U Type lui Instruction Interpreted\n");

    pc += 4;
    return 1;
}

/**
 * This method handles U type instructions, specifically the auipc instruction.
 */
int handleUAuipcInstruction(struct Instruction instr) {
    uint8_t rd = instr.bits7_11;
    int32_t imm = ((instr.bits25_31 << 25) 
        | (instr.bits20_24 << 20) 
        | (instr.bits15_19 << 15) 
        | (instr.bits12_14 << 12));

    registers[rd] = imm + pc;
    fprintf(instructionLog, "U Type auipc Instruction Interpreted\n");

    pc += 4;
    return 1;
}

/**
 * This method handles J type instructions, specifically the jal instruction.
 */
int handleJJalInstruction(struct Instruction instr) {
    uint8_t rd = instr.bits7_11;
    int32_t imm = 
        ((instr.bits25_31 & 0x40) << 14) | 
        ((instr.bits25_31 & 0x3F) << 5) | 
        ((instr.bits20_24 & 0x1E) << 0) | 
        ((instr.bits20_24 & 0x01) << 11) | 
        ((instr.bits15_19) << 15) | 
        ((instr.bits12_14) << 12);
    imm = (imm << 11) >> 11;

    registers[rd] = pc + 4;
    pc = pc + imm;
    fprintf(instructionLog, "J Type jal Instruction Interpreted\n");
    return 1;
}

/**
 * This method handles I type instructions, specifically the jalr instruction.
 */
int handleIJalrInstruction(struct Instruction instr) {
    uint8_t rd = instr.bits7_11;
    uint8_t rs1 = instr.bits15_19;
    int32_t imm = (instr.bits25_31 << 5) | (instr.bits20_24);
    imm = (imm << 20) >> 20;
    uint8_t funct3 = instr.bits12_14;

    
    registers[rd] = pc + 4;
    pc = (registers[rs1] + imm) & 0xFFFFFFFE;
    fprintf(instructionLog, "I Type jalr Instruction Interpreted\n");
    return 1;
}

/**
 * This method is a very basic way of handling any ecall or ebreak instructions.
 */
int handleIEcallEbreakInstruction(struct Instruction instr) {
    uint8_t rd = instr.bits7_11;
    uint8_t rs1 = instr.bits15_19;
    int32_t imm = (instr.bits25_31 << 5) | (instr.bits20_24);
    imm = (imm << 20) >> 20;
    uint8_t funct3 = instr.bits12_14;

    if (imm == 0x0) {
        switch (registers[17]) {
            // Print Integer ecall
            case 1:
                printf("%d", (int32_t)registers[10]);
                fprintf(instructionLog, "I Type ecall Print Integer Instruction Interpreted\n");
                break;
            // Print String ecall
            case 4:
                printf("%s", (char *)&memory[registers[10]]);
                fprintf(instructionLog, "I Type ecall Print String Instruction Interpreted\n");
                break;
            // Print Hexadecimal ecall
            case 34:
                printf("%x", (int32_t)registers[10]);
                fprintf(instructionLog, "I Type ecall Print Integer as Hex Instruction Interpreted\n");
                break;
            // Print Binary ecall
            case 35:
                // TO DO ----------
                break;
            // Read Integer ecall
            case 5:
                int32_t value;
                value = scanf("%d", &value);
                registers[10] = (uint32_t)value;
                fprintf(instructionLog, "I Type ecall Read Integer Instruction Interpreted\n");
                break;
            case 8:
            default:
                fprintf(instructionLog, "Unrecognized ecall Instruction Detected\n");
                perror("Unrecognized ecall Instruction Detected\n");
                return 0;
        }
    }
    else {
        perror("I Type ebreak Instruction Detected\n");
        printf("I Type ebreak Instruction Detected, Terminating Program\n");
        return 0;
    }

    pc += 4;
    return 1;
}



/**
 * A private helper method that should load a word (4 Bytes) from memory given a specific offset
 */
uint32_t loadWord(uint32_t offset) {
    uint32_t word = (uint32_t)memory[offset] 
        | (((uint32_t)memory[offset + 1]) << 8) 
        | (((uint32_t)memory[offset + 2]) << 16) 
        | (((uint32_t)memory[offset + 3]) << 24);
    return word;
}

/**
 * A private helper method that should load a halfword (2 Bytes) from memory given a specific offset
 */
uint32_t loadHalf(uint32_t offset) {
    uint32_t half = (uint32_t)memory[offset] 
        | (((uint32_t)memory[offset + 1]) << 8);
    return half;
}

/**
 * A private helper method that should load a byte (1 Bytes) from memory given a specific offset
 */
uint32_t loadByte(uint32_t offset) {
    uint32_t byte = (uint32_t)memory[offset];
    return byte;
}

/**
 * A private helper method that should save a word (4 Bytes) to memory given a specific offset
 */
void saveWord(uint32_t offset, uint32_t word) {
    memory[offset] = word & 0x000000FF;
    memory[offset + 1] = (word & 0x0000FF00) >> 8;
    memory[offset + 2] = (word & 0x00FF0000) >> 16;
    memory[offset + 3] = (word & 0xFF000000) >> 24;
}

/**
 * A private helper method that should save a halfword (2 Bytes) to memory given a specific offset
 */
void saveHalf(uint32_t offset, uint32_t word) {
    memory[offset] = word & 0x000000FF;
    memory[offset + 1] = (word & 0x0000FF00) >> 8;
}

/**
 * A private helper method that should save a byte (1 Bytes) to memory given a specific offset
 */
void saveByte(uint32_t offset, uint32_t word) {
    memory[offset] = word & 0x000000FF;
}