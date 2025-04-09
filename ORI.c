/*
 * Author: Ol' Jim
 * Date: 06/13/2012
 * ByteForge Systems
 * MIPS-Translatron 3000
 */

// dont get paid enough to implement

#include "Instruction.h"

// Function to encode the "ORI" instruction with an immediate value into binary
void ori_immd_assm(void) {
    // Check if the operation code is "ORI", else set state to WRONG_COMMAND
    if (strcmp(OP_CODE, "ORI") != 0) {
        state = WRONG_COMMAND;  // Set state to WRONG_COMMAND if the opcode doesn't match
        return;
    }

    // Check if the parameters are of the correct types (REGISTER, REGISTER, IMMEDIATE)
    if (PARAM1.type != REGISTER || PARAM2.type != REGISTER || PARAM3.type != IMMEDIATE) {
        state = INVALID_PARAM;  // Set state to INVALID_PARAM if any parameter type is incorrect
        return;
    }

    // Set the opcode for ORI in the instruction (6-bit field for opcode)
    setBits_str(31, "001101");

    // Set the destination register (Rt) value (bits 20-16)
    setBits_num(20, PARAM1.value, 5);

    // Set the source register (Rs) value (bits 25-21)
    setBits_num(25, PARAM2.value, 5);

    // Set the immediate value (bits 15-0)
    setBits_num(15, PARAM3.value, 16);

    // Mark encoding as complete
    state = COMPLETE_ENCODE;
}

// Function to decode the "ORI" instruction from binary to assembly
void ori_immd_bin(void) {
    // Check if the opcode matches "ORI" (001101) and set state to WRONG_COMMAND if not
    if (checkBits(31, "001101") != 0) {
        state = WRONG_COMMAND;  // Set state to WRONG_COMMAND if opcode is incorrect
        return;
    }

    // Extract Rs (bits 25-21), Rt (bits 20-16), and immediate value (bits 15-0) from binary
    uint32_t Rs = getBits(25, 5);  // Extract source register Rs (5 bits)
    uint32_t Rt = getBits(20, 5);  // Extract destination register Rt (5 bits)
    uint32_t imm16 = getBits(15, 16);  // Extract the 16-bit immediate value

    // Set the operation name to "ORI"
    setOp("ORI");

    // Set the decoded parameters for the instruction (destination register, source register, and immediate value)
    setParam(1, REGISTER, Rt);  // Set parameter 1 (Rt) as a REGISTER
    setParam(2, REGISTER, Rs);  // Set parameter 2 (Rs) as a REGISTER
    setParam(3, IMMEDIATE, imm16);  // Set parameter 3 (immediate value) as an IMMEDIATE

    // Mark decoding as complete
    state = COMPLETE_DECODE;
}
