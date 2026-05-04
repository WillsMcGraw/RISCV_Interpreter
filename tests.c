#include "tests.h"

void testManager() {
    int RInstructionResults = testRInstructions();
    if (RInstructionResults) {
        fprintf(instructionLog, "R Instruction Tests Passed\n\n");
    }
    else {
        fprintf(instructionLog, "R Instruction Tests Failed\n\n");
    }

    int IInstructionResults = testIInstructions();
    if (IInstructionResults) {
        fprintf(instructionLog, "I Instruction Tests Passed\n\n");
    }
    else {
        fprintf(instructionLog, "I Instruction Tests Failed\n\n");
    }
}

/**
 * this is a test method meant to check each of the different R type instructions
 */
int testRInstructions() {
    setRegistersToZero();
    registers[6] = 2;
    registers[7] = 3;

    // add x5, x7, x6
    // rd = 5, rs1 = 6, rs2 = 7, funct7 = 0x00, funct3 = 0x0 
    uint32_t r_add_instr = 0b00000000011000111000001010110011;
    struct Instruction parsed_add_instr = parseInstruction(r_add_instr);
    interpret(parsed_add_instr);
    if (registers[5] != 5) {
        printf("Add Instruction Failed\n");
        return 0;
    }
    registers[5] = 0;

    // sub x5, x6, x7
    // rd = 5, rs1 = 7, rs2 = 6, funct7 = 0x20, funct3 = 0x0
    uint32_t r_sub_instr = 0b01000000011100110000001010110011;
    struct Instruction parsed_sub_instr = parseInstruction(r_sub_instr);
    interpret(parsed_sub_instr);
    if (registers[5] != -1) {
        printf("Sub Intsruction Failed\n");
        return 0;
    }
    registers[5] = 0;

    // xor x5, x6, x7
    // rd = 5, rs1 = 6, rs2 = 7, funct7 = 0x00, funct3 = 0x4
    uint32_t r_xor_instr = 0b00000000011100110100001010110011;
    struct Instruction parsed_xor_instr = parseInstruction(r_xor_instr);
    interpret(parsed_xor_instr);
    if (registers[5] != 1) {
        printf("Xor Instruction Failed\n");
        return 0;
    }
    registers[5] = 0;

    // or x5, x6, x7
    // rd = 5, rs1 = 6, rs2 = 7, funct7 = 0x00, funct3 = 0x6
    uint32_t r_or_instr = 0b00000000011100110110001010110011;
    struct Instruction parsed_or_instr = parseInstruction(r_or_instr);
    interpret(parsed_or_instr);
    if (registers[5] != 3) {
        printf("Or Instruction Failed\n");
        return 0;
    }
    registers[5] = 0;

    // and x5, x6, x7
    // rd = 5, rs1 = 6, rs2 = 7, funct7 = 0x00, funct3 = 0x7
    uint32_t r_and_instr = 0b00000000011100110111001010110011;
    struct Instruction parsed_and_instr = parseInstruction(r_and_instr);
    interpret(parsed_and_instr);
    if (registers[5] != 2) {
        printf("And Instruction Failed\n");
        return 0;
    }
    registers[5] = 0;


    // sll x5, x6, x7
    // rd = 5, rs1 = 6, rs2 = 7, funct7 = 0x00, funct3 = 0x1
    uint32_t r_sll_instr = 0b00000000011100110001001010110011;
    struct Instruction parsed_sll_instr = parseInstruction(r_sll_instr);
    interpret(parsed_sll_instr);
    if (registers[5] != 16) {
        printf("Sll Instruction Failed\n");
        return 0;
    }
    registers[5] = 0;


    // srl x5, x6, x7
    // rd = 5, rs1 = 6, rs2 = 7, funct7 = 0x00, funct3 = 0x5
    uint32_t r_srl_instr = 0b00000000011100110101001010110011;
    struct Instruction parsed_srl_instr = parseInstruction(r_srl_instr);
    interpret(parsed_srl_instr);
    if (registers[5] != 0) {
        printf("Srl Instruction Failed\n");
        return 0;
    }
    registers[5] = 0;


    // sra x5, x6, x7
    // rd = 5, rs1 = 6, rs2 = 7, funct7 = 0x20, funct3 = 0x5
    uint32_t r_sra_instr = 0b01000000011100110101001010110011;
    struct Instruction parsed_sra_instr = parseInstruction(r_sra_instr);
    interpret(parsed_sra_instr);
    if (registers[5] != 0) {
        printf("Sra Instruction Failed\n");
        return 0;
    }
    registers[5] = 0;


    // slt x5, x6, x7
    // rd = 5, rs1 = 6, rs2 = 7, funct7 = 0x00, funct3 = 0x2
    uint32_t r_slt_instr = 0b00000000011100110010001010110011;
    struct Instruction parsed_slt_instr = parseInstruction(r_slt_instr);
    interpret(parsed_slt_instr);
    if (registers[5] != 1) {
        printf("Slt Instruction Failed\n");
        return 0;
    }
    registers[5] = 0;


    // sltu x5, x6, x7
    // rd = 5, rs1 = 6, rs2 = 7, funct7 = 0x00, funct3 = 0x3
    uint32_t r_sltu_instr = 0b00000000011100110011001010110011;
    struct Instruction parsed_sltu_instr = parseInstruction(r_sltu_instr);
    interpret(parsed_sltu_instr);
    if (registers[5] != 1) {
        printf("Sltu Instruction Failed\n");
        return 0;
    }
    registers[5] = 0;
}

/**
 * A method to test the I Instruction interpreting
 */
int testIInstructions() {
    setRegistersToZero();
    registers[6] = 2;
    registers[7] = 3;

    // addi x5, x6, 10
    // rd = 5, rs1 = 6, imm = 10
    uint32_t i_addi_instr = 0b00000000101000110000001010010011;
    struct Instruction parsed_addi_instr = parseInstruction(i_addi_instr);
    interpret(parsed_addi_instr);
    if (registers[5] != 12) {
        printf("Addi Instruction Failed\n");
        return 0;
    }
    registers[5] = 0;


    // xori x5, x6, 10
    // rd = 5, rs1 = 6, imm = 10
    uint32_t i_xori_instr = 0b00000000101000110100001010010011;
    struct Instruction parsed_xori_instr = parseInstruction(i_xori_instr);
    interpret(parsed_xori_instr);
    if (registers[5] != (0x2 ^ 10)) {
        printf("Xori Instruction Failed\n");
        return 0;
    }
    registers[5] = 0;


    // ori x5, x6, 10
    // rd = 5, rs1 = 6, imm = 10
    uint32_t i_ori_instr = 0b00000000101000110110001010010011;
    struct Instruction parsed_ori_instr = parseInstruction(i_ori_instr);
    interpret(parsed_ori_instr);
    if (registers[5] != (2 | 10)) {
        printf("Ori Instruction Failed\n");
        return 0;
    }
    registers[5] = 0;


    // andi x5, x6, 0b1100 (12)
    // rd = 5, rs1 = 6, imm = 12
    uint32_t i_andi_instr = 0b00000000110000110111001010010011;
    struct Instruction parsed_andi_instr = parseInstruction(i_andi_instr);
    interpret(parsed_andi_instr);
    if (registers[5] != (2 & 12)) {
        printf("Andi Instruction Failed\n");
        return 0;
    }
    registers[5] = 0;


    // slti x5, x6, 5
    // rd = 5, rs1 = 6, imm = 5
    uint32_t i_slti_instr = 0b00000000010100110010001010010011;
    struct Instruction parsed_slti_instr = parseInstruction(i_slti_instr);
    interpret(parsed_slti_instr);
    if (registers[5] != 1) {
        printf("Slti Instruction Failed\n");
        return 0;
    }
    registers[5] = 0;


    // sltiu x5, x6, 5
    // rd = 5, rs1 = 6, imm = 5
    uint32_t i_sltiu_instr = 0b00000000010100110011001010010011;
    struct Instruction parsed_sltiu_instr = parseInstruction(i_sltiu_instr);
    interpret(parsed_sltiu_instr);
    if (registers[5] != 1) {
        printf("Sltiu Instruction Failed\n");
        return 0;
    }
    registers[5] = 0;


    // slli x5, x6, 2
    // rd = 5, rs1 = 6, shamt = 2
    uint32_t i_slli_instr = 0b00000000001000110001001010010011;
    struct Instruction parsed_slli_instr = parseInstruction(i_slli_instr);
    interpret(parsed_slli_instr);
    if (registers[5] != (2 << 2)) {
        printf("Slli Instruction Failed\n");
        return 0;
    }
    registers[5] = 0;


    // srli x5, x6, 1
    // rd = 5, rs1 = 6, shamt = 1
    uint32_t i_srli_instr = 0b00000000000100110101001010010011;
    struct Instruction parsed_srli_instr = parseInstruction(i_srli_instr);
    interpret(parsed_srli_instr);
    if (registers[5] != (2 >> 1)) {
        printf("Srli Instruction Failed\n");
        return 0;
    }
    registers[5] = 0;


    // srai x5, x6, 1
    // rd = 5, rs1 = 6, shamt = 1, funct7 = 0x20
    uint32_t i_srai_instr = 0b01000000000100110101001010010011;
    struct Instruction parsed_srai_instr = parseInstruction(i_srai_instr);
    interpret(parsed_srai_instr);
    if (registers[5] != ((int32_t)2 >> 1)) {
        printf("Srai Instruction Failed\n");
        return 0;
    }
    registers[5] = 0;
}

void setRegistersToZero() {
    for (uint32_t i = 0; i < 32; i++) {
        registers[i] = 0;
    }
}