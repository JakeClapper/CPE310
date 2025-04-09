/*
 * Author: Ol' Jim
 * Date: 06/13/2012
 * ByteForge Systems
 * MIPS-Translatron 3000
 */

// give this to the intern

#include "Instruction.h"

// Function to encode the "SLTI" (Set on Less Than Immediate) instruction for registers and immediate value into binary
void slti_immd_assm(void) {
    // Check if the operation code is "SLTI"
    if (strcmp(OP_CODE, "SLTI") != 0) {
        state = WRONG_COMMAND;  // Set state to WRONG_COMMAND if the opcode does not match
        return;
    }

    // Check that the parameter types are correct: 
    // PARAM1 and PARAM2 should be registers, and PARAM3 should be an immediate
    if (PARAM1.type != REGISTER || PARAM2.type != REGISTER || PARAM3.type != IMMEDIATE) {
        state = INVALID_PARAM;  // Set state to INVALID_PARAM if any parameter is incorrect
        return;
    }

    // Set the opcode for SLTI (immediate comparison)
    setBits_str(31, "001010");

    // Set the destination register (Rt) for the result of the comparison
    setBits_num(20, PARAM1.value, 5);  // Rt as the destination register

    // Set the source register (Rs) which holds the value to compare
    setBits_num(25, PARAM2.value, 5);  // Rs as the source register

    // Set the immediate value for comparison
    setBits_num(15, PARAM3.value, 16);  // Immediate value for SLTI instruction

    // Mark encoding as complete
    state = COMPLETE_ENCODE;
}

// Function to decode the "SLTI" instruction from binary to assembly
void slti_immd_bin(void) {
    // Confirm that the opcode (001010) matches SLTI
    if (checkBits(31, "001010") != 0) {
        state = WRONG_COMMAND;  // Set state to WRONG_COMMAND if the opcode does not match
        return;
    }

    // Extract Rs, Rt, and the immediate value from the binary instruction
    uint32_t Rs = getBits(25, 5);  // Extract Rs (source register)
    uint32_t Rt = getBits(20, 5);  // Extract Rt (destination register)
    uint32_t imm16 = getBits(15, 16);  // Extract the 16-bit immediate value

    // Set operation and parameters for the decoded instruction
    setOp("SLTI");  // Set operation to SLTI

    // Set the parameters: Rt is the destination register, Rs is the source register, and imm16 is the immediate value
    setParam(1, REGISTER, Rt);  // Set destination register (Rt)
    setParam(2, REGISTER, Rs);  // Set source register (Rs)
    setParam(3, IMMEDIATE, imm16);  // Set the immediate value

    // Indicate that the decoding is complete
    state = COMPLETE_DECODE;
}
