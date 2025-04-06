#include "Instruction.h"
// Author: Kayden Yost

/**
 * Function: mult_reg_assm
 * -----------------------
 * Encodes the "MULT" (Multiply) instruction into binary format based on the provided parameters.
 * 
 * Preconditions:
 * - OP_CODE must be "MULT".
 * - PARAM1 and PARAM2 must be REGISTER types.
 * - PARAM1.value and PARAM2.value must be within the valid range of 0-31.
 * 
 * Postconditions:
 * - Sets the binary representation of the instruction using `setBits_str` and `setBits_num`.
 * - Updates the `state` to COMPLETE_ENCODE if successful, or an error state otherwise.
 */
void mult_reg_assm(void) {
    // Check if the operation code matches "MULT".
    if (strcmp(OP_CODE, "MULT") != 0) {
        state = WRONG_COMMAND; // Set state to WRONG_COMMAND if the opcode is incorrect.
        return;
    }

    // Validate that the first parameter is a REGISTER.
    if (PARAM1.type != REGISTER) {
        state = MISSING_REG; // Set state to MISSING_REG if PARAM1 is not a REGISTER.
        return;
    }

    // Validate that the second parameter is a REGISTER.
    if (PARAM2.type != REGISTER) {
        state = MISSING_REG; // Set state to MISSING_REG if PARAM2 is not a REGISTER.
        return;
    }

    // Validate that the first register value is within the valid range (0-31).
    if (PARAM1.value > 31) {
        state = INVALID_REG; // Set state to INVALID_REG if PARAM1's value is invalid.
        return;
    }
    
    // Validate that the second register value is within the valid range (0-31).
    if (PARAM2.value > 31) {
        state = INVALID_REG; // Set state to INVALID_REG if PARAM2's value is invalid.
        return;
    }

    // Set the opcode bits for "MULT".
    setBits_str(31, "000000");

    // Set the function code bits for "MULT".
    setBits_str(5, "011000");

    // Set the first source register (Rs) bits.
    setBits_num(25, PARAM1.value, 5);

    // Set the second source register (Rt) bits.
    setBits_num(20, PARAM2.value, 5);

    // Update the state to indicate successful encoding.
    state = COMPLETE_ENCODE;
}

/**
 * Function: mult_reg_bin
 * ----------------------
 * Decodes a binary representation of the "MULT" (Multiply) instruction into its components.
 * 
 * Preconditions:
 * - The binary instruction must have the opcode "000000" at bits 31-26 and the function code "011000" at bits 5-0.
 * 
 * Postconditions:
 * - Extracts the source registers (Rs and Rt).
 * - Sets the operation and parameters using `setOp` and `setParam`.
 * - Updates the `state` to COMPLETE_DECODE if successful, or an error state otherwise.
 */
void mult_reg_bin(void) {
    // Check if the opcode and function code in the binary instruction match "MULT".
    if (checkBits(31, "000000") != 0 || checkBits(5, "011000") != 0) {
        state = WRONG_COMMAND; // Set state to WRONG_COMMAND if the opcode or function code is incorrect.
        return;
    }

    // Extract the first source register (Rs) from bits 25-21.
    uint32_t Rs = getBits(25, 5);

    // Extract the second source register (Rt) from bits 20-16.
    uint32_t Rt = getBits(20, 5);

    // Set the operation name to "MULT".
    setOp("MULT");

    // Set the first source register parameter.
    setParam(1, REGISTER, Rs);

    // Set the second source register parameter.
    setParam(2, REGISTER, Rt);

    // Update the state to indicate successful decoding.
    state = COMPLETE_DECODE;
}